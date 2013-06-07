/*
  BRISK - Binary Robust Invariant Scalable Keypoints
  Reference implementation of
  [1] Stefan Leutenegger,Margarita Chli and Roland Siegwart, BRISK:
  Binary Robust Invariant Scalable Keypoints, in Proceedings of
  the IEEE International Conference on Computer Vision (ICCV2011).

  Copyright (C) 2011  The Autonomous Systems Lab (ASL), ETH Zurich,
  Stefan Leutenegger, Simon Lynen and Margarita Chli.

  This file is part of BRISK.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  * Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
  * Neither the name of the ASL nor the names of its contributors may be
  used to endorse or promote products derived from this software without
  specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "image/keypoint_detector/brisk_impl.h"
#include "image/keypoint_detector/keypoint.h"

#include <agast/oast9_16.h>
#include <agast/agast7_12s.h>
#include <agast/agast5_8.h>
#include <glog/logging.h>
#include <stdlib.h>
#ifdef THEIA_USE_SSE
#include <tmmintrin.h>
#endif

namespace theia {
namespace {
typedef unsigned char uchar;
// this is needed to avoid aliasing issues with the __m128i data type:
#ifdef __GNUC__
typedef unsigned char __attribute__ ((__may_alias__)) UCHAR_ALIAS;
typedef unsigned short __attribute__ ((__may_alias__)) UINT16_ALIAS;
typedef unsigned int __attribute__ ((__may_alias__)) UINT32_ALIAS;
typedef unsigned long int __attribute__ ((__may_alias__)) UINT64_ALIAS;
typedef int __attribute__ ((__may_alias__)) INT32_ALIAS;
typedef uint8_t __attribute__ ((__may_alias__)) U_INT8T_ALIAS;
#endif
#ifdef _MSC_VER
// Todo: find the equivalent to may_alias
#define UCHAR_ALIAS unsigned char //__declspec(noalias)
#define UINT32_ALIAS unsigned int //__declspec(noalias)
#define __inline__ __forceinline
#endif
}  // namespace

const float BriskScaleSpace::safetyFactor_ = 1.0;
const float BriskScaleSpace::basicSize_ = 12.0;

// construct telling the octaves number:
BriskScaleSpace::BriskScaleSpace(uint8_t _octaves) {
  if (_octaves==0)
    layers_=1;
  else
    layers_=2*_octaves;
}

// construct the image pyramids
void BriskScaleSpace::constructPyramid(const Image<unsigned char>& image) {
  // set correct size:
  pyramid_.clear();

  // fill the pyramid:
  pyramid_.push_back(BriskLayer(image.Clone()));
  if (layers_>1) {
    pyramid_.push_back(BriskLayer(pyramid_.back(),
                                  BriskLayer::CommonParams::TWOTHIRDSAMPLE));
  }
  const int octaves2=layers_;

  for (uint8_t i=2; i<octaves2; i+=2) {
    pyramid_.push_back(BriskLayer(pyramid_[i-2],
                                  BriskLayer::CommonParams::HALFSAMPLE));
    pyramid_.push_back(BriskLayer(pyramid_[i-1],
                                  BriskLayer::CommonParams::HALFSAMPLE));
  }
}

void BriskScaleSpace::getKeypoints(const uint8_t _threshold,
                                   std::vector<Keypoint*>* keypoints) {
  keypoints->reserve(2000);

  // assign thresholds
  threshold_=_threshold;
  safeThreshold_ = threshold_*safetyFactor_;
  std::vector<std::vector<CvPoint> > agastPoints;
  agastPoints.resize(layers_);

  // go through the octaves and intra layers and calculate fast corner scores:
  for (uint8_t i = 0; i<layers_; i++) {
    // call OAST16_9 without nms
    BriskLayer& l=pyramid_[i];
    l.getAgastPoints(safeThreshold_,agastPoints[i]);
  }

  if (layers_==1) {
    // just do a simple 2d subpixel refinement...
    const int num=agastPoints[0].size();
    for (int n=0; n < num; n++) {
      const CvPoint& point=agastPoints.at(0)[n];
      // first check if it is a maximum:
      if (!isMax2D(0, point.x, point.y))
        continue;

      // let's do the subpixel and float scale refinement:
      BriskLayer& l=pyramid_[0];
      register int s_0_0 = l.getAgastScore(point.x-1, point.y-1, 1);
      register int s_1_0 = l.getAgastScore(point.x,   point.y-1, 1);
      register int s_2_0 = l.getAgastScore(point.x+1, point.y-1, 1);
      register int s_2_1 = l.getAgastScore(point.x+1, point.y,   1);
      register int s_1_1 = l.getAgastScore(point.x,   point.y,   1);
      register int s_0_1 = l.getAgastScore(point.x-1, point.y,   1);
      register int s_0_2 = l.getAgastScore(point.x-1, point.y+1, 1);
      register int s_1_2 = l.getAgastScore(point.x,   point.y+1, 1);
      register int s_2_2 = l.getAgastScore(point.x+1, point.y+1, 1);
      float delta_x, delta_y;
      float max = subpixel2D(s_0_0, s_0_1, s_0_2,
                             s_1_0, s_1_1, s_1_2,
                             s_2_0, s_2_1, s_2_2,
                             delta_x, delta_y);

      // store:
      Keypoint* new_keypoint = new Keypoint(point.x + delta_x,
                                            point.y + delta_y,
                                            Keypoint::BRISK);
      new_keypoint->set_strength(max);
      new_keypoint->set_scale(0);
      keypoints->push_back(new_keypoint);
      /*
        keypoints->push_back(cv::KeyPoint(float(point.x)+delta_x,
        float(point.y)+delta_y,
        basicSize_,
        -1,
        max,
        0));
      */
    }
    return;
  }

  float x,y,scale,score;
  for (uint8_t i = 0; i<layers_; i++) {
    BriskLayer& l=pyramid_[i];
    const int num=agastPoints[i].size();
    if (i==layers_-1) {
      for (int n=0; n < num; n++) {
        const CvPoint& point=agastPoints.at(i)[n];
        // consider only 2D maxima...
        if (!isMax2D(i, point.x, point.y))
          continue;

        bool ismax;
        float dx, dy;
        getScoreMaxBelow(i, point.x, point.y,
                         l.getAgastScore(point.x, point.y, safeThreshold_),
                         ismax,
                         dx, dy);
        if (!ismax)
          continue;

        // get the patch on this layer:
        register int s_0_0 = l.getAgastScore(point.x-1, point.y-1, 1);
        register int s_1_0 = l.getAgastScore(point.x,   point.y-1, 1);
        register int s_2_0 = l.getAgastScore(point.x+1, point.y-1, 1);
        register int s_2_1 = l.getAgastScore(point.x+1, point.y,   1);
        register int s_1_1 = l.getAgastScore(point.x,   point.y,   1);
        register int s_0_1 = l.getAgastScore(point.x-1, point.y,   1);
        register int s_0_2 = l.getAgastScore(point.x-1, point.y+1, 1);
        register int s_1_2 = l.getAgastScore(point.x,   point.y+1, 1);
        register int s_2_2 = l.getAgastScore(point.x+1, point.y+1, 1);
        float delta_x, delta_y;
        float max = subpixel2D(s_0_0, s_0_1, s_0_2,
                               s_1_0, s_1_1, s_1_2,
                               s_2_0, s_2_1, s_2_2,
                               delta_x, delta_y);

        // store:
        Keypoint* new_keypoint =
            new Keypoint((point.x + delta_x)*l.scale() + l.offset(),
                         (point.y + delta_y)*l.scale() + l.offset(),
                         Keypoint::BRISK);
        new_keypoint->set_strength(max);
        new_keypoint->set_scale(l.scale());
        keypoints->push_back(new_keypoint);
        /*
          keypoints->push_back(
          cv::KeyPoint((float(point.x)+delta_x)*l.scale()+l.offset(),
          (float(point.y)+delta_y)*l.scale()+l.offset(),
          basicSize_*l.scale(), -1, max,i));
        */
      }
    } else {
      // not the last layer:
      for (int n=0; n < num; n++) {
        const CvPoint& point=agastPoints.at(i)[n];

        // first check if it is a maximum:
        if (!isMax2D(i, point.x, point.y))
          continue;

        // let's do the subpixel and float scale refinement:
        bool ismax;
        score=refine3D(i,point.x, point.y,x,y,scale,ismax);
        if (!ismax) {
          continue;
        }

        // finally store the detected keypoint:
        if (score>float(threshold_)) {
          Keypoint* new_keypoint = new Keypoint(x, y, Keypoint::BRISK);
          new_keypoint->set_strength(score);
          new_keypoint->set_scale(scale);
          keypoints->push_back(new_keypoint);

          //keypoints->push_back(cv::KeyPoint(x, y, basicSize_*scale, -1, score,i));
        }
      }
    }
  }
}

// interpolated score access with recalculation when needed:
inline int BriskScaleSpace::getScoreAbove(const uint8_t layer,
                                          const int x_layer, const int y_layer) {
  CHECK_LT(layer, layers_ - 1);
  BriskLayer& l=pyramid_[layer+1];
  if (layer%2==0) { // octave
    const int sixths_x=4*x_layer-1;
    const int x_above=sixths_x/6;
    const int sixths_y=4*y_layer-1;
    const int y_above=sixths_y/6;
    const int r_x=(sixths_x%6);
    const int r_x_1=6-r_x;
    const int r_y=(sixths_y%6);
    const int r_y_1=6-r_y;
    uint8_t score = 0xFF&((r_x_1*r_y_1*l.getAgastScore(x_above,y_above,1) +
                           r_x*r_y_1*l.getAgastScore(x_above+1,y_above,1) +
                           r_x_1*r_y*l.getAgastScore(x_above,y_above+1,1) +
                           r_x*r_y*l.getAgastScore(x_above+1,y_above+1,1)+18)/36);

    return score;
  } else { // intra
    const int eighths_x=6*x_layer-1;
    const int x_above=eighths_x/8;
    const int eighths_y=6*y_layer-1;
    const int y_above=eighths_y/8;
    const int r_x=(eighths_x%8);
    const int r_x_1=8-r_x;
    const int r_y=(eighths_y%8);
    const int r_y_1=8-r_y;
    uint8_t score = 0xFF&((r_x_1*r_y_1*l.getAgastScore(x_above,y_above,1) +
                           r_x*r_y_1*l.getAgastScore(x_above+1,y_above,1) +
                           r_x_1*r_y*l.getAgastScore(x_above,y_above+1,1) +
                           r_x*r_y*l.getAgastScore(x_above+1,y_above+1,1)+32)/64);
    return score;
  }
}
inline int BriskScaleSpace::getScoreBelow(const uint8_t layer,
                                          const int x_layer, const int y_layer) {
  CHECK_GT(layer, 0);
  BriskLayer& l=pyramid_[layer-1];
  int sixth_x;
  int quarter_x;
  float xf;
  int sixth_y;
  int quarter_y;
  float yf;

  // scaling:
  float offs;
  float area;
  int scaling;
  int scaling2;

  if (layer%2==0) { // octave
    sixth_x=8*x_layer+1;
    xf=float(sixth_x)/6.0;
    sixth_y=8*y_layer+1;
    yf=float(sixth_y)/6.0;

    // scaling:
    offs = 2.0/3.0;
    area=4.0*offs*offs;
    scaling = 4194304.0/area;
    scaling2=float(scaling)*area;
  } else {
    quarter_x=6*x_layer+1;
    xf=float(quarter_x)/4.0;
    quarter_y=6*y_layer+1;
    yf=float(quarter_y)/4.0;

    // scaling:
    offs = 3.0/4.0;
    area=4.0*offs*offs;
    scaling = 4194304.0/area;
    scaling2=float(scaling)*area;
  }

  // calculate borders
  const float x_1=xf-offs;
  const float x1=xf+offs;
  const float y_1=yf-offs;
  const float y1=yf+offs;

  const int x_left=int(x_1+0.5);
  const int y_top=int(y_1+0.5);
  const int x_right=int(x1+0.5);
  const int y_bottom=int(y1+0.5);

  // overlap area - multiplication factors:
  const float r_x_1=float(x_left)-x_1+0.5;
  const float r_y_1=float(y_top)-y_1+0.5;
  const float r_x1=x1-float(x_right)+0.5;
  const float r_y1=y1-float(y_bottom)+0.5;
  const int dx=x_right-x_left-1;
  const int dy=y_bottom-y_top-1;
  const int A=(r_x_1*r_y_1)*scaling;
  const int B=(r_x1*r_y_1)*scaling;
  const int C=(r_x1*r_y1)*scaling;
  const int D=(r_x_1*r_y1)*scaling;
  const int r_x_1_i=r_x_1*scaling;
  const int r_y_1_i=r_y_1*scaling;
  const int r_x1_i=r_x1*scaling;
  const int r_y1_i=r_y1*scaling;

  // first row:
  int ret_val=A*int(l.getAgastScore(x_left,y_top,1));
  for (int X=1; X<=dx; X++) {
    ret_val+=r_y_1_i*int(l.getAgastScore(x_left+X,y_top,1));
  }
  ret_val+=B*int(l.getAgastScore(x_left+dx+1,y_top,1));
  // middle ones:
  for (int Y=1; Y<=dy; Y++) {
    ret_val+=r_x_1_i*int(l.getAgastScore(x_left,y_top+Y,1));


    for (int X=1; X<=dx; X++) {
      ret_val+=int(l.getAgastScore(x_left+X,y_top+Y,1))*scaling;
    }
    ret_val+=r_x1_i*int(l.getAgastScore(x_left+dx+1,y_top+Y,1));
  }
  // last row:
  ret_val+=D*int(l.getAgastScore(x_left,y_top+dy+1,1));
  for (int X=1; X<=dx; X++) {
    ret_val+=r_y1_i*int(l.getAgastScore(x_left+X,y_top+dy+1,1));
  }
  ret_val+=C*int(l.getAgastScore(x_left+dx+1,y_top+dy+1,1));

  return ((ret_val+scaling2/2)/scaling2);
}

inline bool BriskScaleSpace::isMax2D(const uint8_t layer,
                                     const int x_layer, const int y_layer) {
  const Image<unsigned char>& scores = pyramid_[layer].scores();
  const int scorescols = scores.Cols();
  const uchar* data=scores.Data() + y_layer*scorescols + x_layer;
  // decision tree:
  const uchar center = (*data);
  data--;
  const uchar s_10=*data;
  if (center<s_10) return false;
  data+=2;
  const uchar s10=*data;
  if (center<s10) return false;
  data-=(scorescols+1);
  const uchar s0_1=*data;
  if (center<s0_1) return false;
  data+=2*scorescols;
  const uchar s01=*data;
  if (center<s01) return false;
  data--;
  const uchar s_11=*data;
  if (center<s_11) return false;
  data+=2;
  const uchar s11=*data;
  if (center<s11) return false;
  data-=2*scorescols;
  const uchar s1_1=*data;
  if (center<s1_1) return false;
  data-=2;
  const uchar s_1_1=*data;
  if (center<s_1_1) return false;

  // reject neighbor maxima
  std::vector<int> delta;
  // put together a list of 2d-offsets to where the maximum is also reached
  if (center==s_1_1) {
    delta.push_back(-1);
    delta.push_back(-1);
  }
  if (center==s0_1) {
    delta.push_back(0);
    delta.push_back(-1);
  }
  if (center==s1_1) {
    delta.push_back(1);
    delta.push_back(-1);
  }
  if (center==s_10) {
    delta.push_back(-1);
    delta.push_back(0);
  }
  if (center==s10) {
    delta.push_back(1);
    delta.push_back(0);
  }
  if (center==s_11) {
    delta.push_back(-1);
    delta.push_back(1);
  }
  if (center==s01) {
    delta.push_back(0);
    delta.push_back(1);
  }
  if (center==s11) {
    delta.push_back(1);
    delta.push_back(1);
  }
  const unsigned int deltasize=delta.size();
  if (deltasize!=0) {
    // in this case, we have to analyze the situation more carefully:
    // the values are gaussian blurred and then we really decide
    data=scores.Data() + y_layer*scorescols + x_layer;
    int smoothedcenter=4*center+2*(s_10+s10+s0_1+s01)+s_1_1+s1_1+s_11+s11;
    for (unsigned int i=0; i<deltasize;i+=2) {
      data = scores.Data() + (y_layer-1+delta[i+1])*scorescols +
             x_layer+delta[i]-1;
      int othercenter=*data;
      data++;
      othercenter+=2*(*data);
      data++;
      othercenter+=*data;
      data+=scorescols;
      othercenter+=2*(*data);
      data--;
      othercenter+=4*(*data);
      data--;
      othercenter+=2*(*data);
      data+=scorescols;
      othercenter+=*data;
      data++;
      othercenter+=2*(*data);
      data++;
      othercenter+=*data;
      if (othercenter>smoothedcenter)
        return false;
    }
  }
  return true;
}

// 3D maximum refinement centered around (x_layer,y_layer)
inline float BriskScaleSpace::refine3D(const uint8_t layer,
                                       const int x_layer, const int y_layer,
                                       float& x, float& y, float& scale,
                                       bool& ismax) {
  ismax=true;
  BriskLayer& thisLayer=pyramid_[layer];
  const int center = thisLayer.getAgastScore(x_layer,y_layer,1);

  // check and get above maximum:
  float delta_x_above, delta_y_above;
  float max_above = getScoreMaxAbove(layer,x_layer, y_layer,
                                     center, ismax,
                                     delta_x_above, delta_y_above);

  if (!ismax) return 0.0;

  float max; // to be returned

  if (layer%2==0) { // on octave
    // treat the patch below:
    float delta_x_below, delta_y_below;
    float max_below_float;
    uchar max_below_uchar=0;
    if (layer==0) {
      // guess the lower intra octave...
      BriskLayer& l=pyramid_[0];
      register int s_0_0 = l.getAgastScore_5_8(x_layer-1, y_layer-1, 1);
      max_below_uchar=s_0_0;
      register int s_1_0 = l.getAgastScore_5_8(x_layer,   y_layer-1, 1);
      if (s_1_0>max_below_uchar) max_below_uchar=s_1_0;
      register int s_2_0 = l.getAgastScore_5_8(x_layer+1, y_layer-1, 1);
      if (s_2_0>max_below_uchar) max_below_uchar=s_2_0;
      register int s_2_1 = l.getAgastScore_5_8(x_layer+1, y_layer,   1);
      if (s_2_1>max_below_uchar) max_below_uchar=s_2_1;
      register int s_1_1 = l.getAgastScore_5_8(x_layer,   y_layer,   1);
      if (s_1_1>max_below_uchar) max_below_uchar=s_1_1;
      register int s_0_1 = l.getAgastScore_5_8(x_layer-1, y_layer,   1);
      if (s_0_1>max_below_uchar) max_below_uchar=s_0_1;
      register int s_0_2 = l.getAgastScore_5_8(x_layer-1, y_layer+1, 1);
      if (s_0_2>max_below_uchar) max_below_uchar=s_0_2;
      register int s_1_2 = l.getAgastScore_5_8(x_layer,   y_layer+1, 1);
      if (s_1_2>max_below_uchar) max_below_uchar=s_1_2;
      register int s_2_2 = l.getAgastScore_5_8(x_layer+1, y_layer+1, 1);
      if (s_2_2>max_below_uchar) max_below_uchar=s_2_2;

      max_below_float = subpixel2D(s_0_0, s_0_1, s_0_2,
                                   s_1_0, s_1_1, s_1_2,
                                   s_2_0, s_2_1, s_2_2,
                                   delta_x_below, delta_y_below);
      max_below_float = max_below_uchar;
    } else {
      max_below_float = getScoreMaxBelow(layer,x_layer, y_layer,
                                         center, ismax,
                                         delta_x_below, delta_y_below);
      if (!ismax) return 0;
    }

    // get the patch on this layer:
    register int s_0_0 = thisLayer.getAgastScore(x_layer-1, y_layer-1,1);
    register int s_1_0 = thisLayer.getAgastScore(x_layer,   y_layer-1,1);
    register int s_2_0 = thisLayer.getAgastScore(x_layer+1, y_layer-1,1);
    register int s_2_1 = thisLayer.getAgastScore(x_layer+1, y_layer,1);
    register int s_1_1 = thisLayer.getAgastScore(x_layer,   y_layer,1);
    register int s_0_1 = thisLayer.getAgastScore(x_layer-1, y_layer,1);
    register int s_0_2 = thisLayer.getAgastScore(x_layer-1, y_layer+1,1);
    register int s_1_2 = thisLayer.getAgastScore(x_layer,   y_layer+1,1);
    register int s_2_2 = thisLayer.getAgastScore(x_layer+1, y_layer+1,1);
    float delta_x_layer, delta_y_layer;
    float max_layer = subpixel2D(s_0_0, s_0_1, s_0_2,
                                 s_1_0, s_1_1, s_1_2,
                                 s_2_0, s_2_1, s_2_2,
                                 delta_x_layer, delta_y_layer);

    // calculate the relative scale (1D maximum):
    if (layer==0) {
      scale=refine1D_2(max_below_float,
                       std::max(float(center),max_layer),
                       max_above,max);
    } else
      scale=refine1D(max_below_float,
                     std::max(float(center),max_layer),
                     max_above,max);

    if (scale>1.0) {
      // interpolate the position:
      const float r0=(1.5-scale)/.5;
      const float r1=1.0-r0;
      x=(r0*delta_x_layer+r1*delta_x_above+float(x_layer))
        *thisLayer.scale()+thisLayer.offset();
      y=(r0*delta_y_layer+r1*delta_y_above+float(y_layer))
        *thisLayer.scale()+thisLayer.offset();
    } else {
      if (layer==0) {
        // interpolate the position:
        const float r0=(scale-0.5)/0.5;
        const float r_1=1.0-r0;
        x=r0*delta_x_layer+r_1*delta_x_below+float(x_layer);
        y=r0*delta_y_layer+r_1*delta_y_below+float(y_layer);
      } else {
        // interpolate the position:
        const float r0=(scale-0.75)/0.25;
        const float r_1=1.0-r0;
        x=(r0*delta_x_layer+r_1*delta_x_below+float(x_layer))
          *thisLayer.scale()+thisLayer.offset();
        y=(r0*delta_y_layer+r_1*delta_y_below+float(y_layer))
          *thisLayer.scale()+thisLayer.offset();
      }
    }
  } else {
    // on intra
    // check the patch below:
    float delta_x_below, delta_y_below;
    float max_below = getScoreMaxBelow(layer,x_layer, y_layer,
                                       center, ismax,
                                       delta_x_below, delta_y_below);
    if (!ismax) return 0.0;

    // get the patch on this layer:
    register int s_0_0 = thisLayer.getAgastScore(x_layer-1, y_layer-1,1);
    register int s_1_0 = thisLayer.getAgastScore(x_layer,   y_layer-1,1);
    register int s_2_0 = thisLayer.getAgastScore(x_layer+1, y_layer-1,1);
    register int s_2_1 = thisLayer.getAgastScore(x_layer+1, y_layer,1);
    register int s_1_1 = thisLayer.getAgastScore(x_layer,   y_layer,1);
    register int s_0_1 = thisLayer.getAgastScore(x_layer-1, y_layer,1);
    register int s_0_2 = thisLayer.getAgastScore(x_layer-1, y_layer+1,1);
    register int s_1_2 = thisLayer.getAgastScore(x_layer,   y_layer+1,1);
    register int s_2_2 = thisLayer.getAgastScore(x_layer+1, y_layer+1,1);
    float delta_x_layer, delta_y_layer;
    float max_layer = subpixel2D(s_0_0, s_0_1, s_0_2,
                                 s_1_0, s_1_1, s_1_2,
                                 s_2_0, s_2_1, s_2_2,
                                 delta_x_layer, delta_y_layer);

    // calculate the relative scale (1D maximum):
    scale=refine1D_1(max_below,
                     std::max(float(center),max_layer),
                     max_above,max);
    if (scale>1.0) {
      // interpolate the position:
      const float r0=4.0-scale*3.0;
      const float r1=1.0-r0;
      x=(r0*delta_x_layer+r1*delta_x_above+float(x_layer))
        *thisLayer.scale()+thisLayer.offset();
      y=(r0*delta_y_layer+r1*delta_y_above+float(y_layer))
        *thisLayer.scale()+thisLayer.offset();
    } else {
      // interpolate the position:
      const float r0=scale*3.0-2.0;
      const float r_1=1.0-r0;
      x=(r0*delta_x_layer+r_1*delta_x_below+float(x_layer))
        *thisLayer.scale()+thisLayer.offset();
      y=(r0*delta_y_layer+r_1*delta_y_below+float(y_layer))
        *thisLayer.scale()+thisLayer.offset();
    }
  }

  // calculate the absolute scale:
  scale*=thisLayer.scale();

  // that's it, return the refined maximum:
  return max;
}

// return the maximum of score patches above or below
inline float BriskScaleSpace::getScoreMaxAbove(const uint8_t layer,
                                               const int x_layer, const int y_layer,
                                               const int threshold, bool& ismax,
                                               float& dx, float& dy) {

  ismax=false;
  // relevant floating point coordinates
  float x_1;
  float x1;
  float y_1;
  float y1;

  // the layer above
  assert(layer+1<layers_);
  BriskLayer& layerAbove=pyramid_[layer+1];

  if (layer%2==0) {
    // octave
    x_1=float(4*(x_layer)-1-2)/6.0;
    x1=float(4*(x_layer)-1+2)/6.0;
    y_1=float(4*(y_layer)-1-2)/6.0;
    y1=float(4*(y_layer)-1+2)/6.0;
  } else {
    // intra
    x_1=float(6*(x_layer)-1-3)/8.0f;
    x1=float(6*(x_layer)-1+3)/8.0f;
    y_1=float(6*(y_layer)-1-3)/8.0f;
    y1=float(6*(y_layer)-1+3)/8.0f;
  }


  // check the first row
  int max_x = x_1+1;
  int max_y = y_1+1;
  float tmp_max;
  float max=layerAbove.getAgastScore(x_1,y_1,1);
  if (max>threshold) return 0;
  for (int x=x_1+1; x<=int(x1); x++) {
    tmp_max=layerAbove.getAgastScore(float(x),y_1,1);
    if (tmp_max>threshold) return 0;
    if (tmp_max>max) {
      max=tmp_max;
      max_x = x;
    }
  }
  tmp_max=layerAbove.getAgastScore(x1,y_1,1);
  if (tmp_max>threshold) return 0;
  if (tmp_max>max) {
    max=tmp_max;
    max_x = int(x1);
  }

  // middle rows
  for (int y=y_1+1; y<=int(y1); y++) {
    tmp_max=layerAbove.getAgastScore(x_1,float(y),1);
    if (tmp_max>threshold) return 0;
    if (tmp_max>max) {
      max=tmp_max;
      max_x = int(x_1+1);
      max_y = y;
    }
    for (int x=x_1+1; x<=int(x1); x++) {
      tmp_max=layerAbove.getAgastScore(x,y,1);
      if (tmp_max>threshold) return 0;
      if (tmp_max>max) {
        max=tmp_max;
        max_x = x;
        max_y = y;
      }
    }
    tmp_max=layerAbove.getAgastScore(x1,float(y),1);
    if (tmp_max>threshold) return 0;
    if (tmp_max>max) {
      max=tmp_max;
      max_x = int(x1);
      max_y = y;
    }
  }

  // bottom row
  tmp_max=layerAbove.getAgastScore(x_1,y1,1);
  if (tmp_max>max) {
    max=tmp_max;
    max_x = int(x_1+1);
    max_y = int(y1);
  }
  for (int x=x_1+1; x<=int(x1); x++) {
    tmp_max=layerAbove.getAgastScore(float(x),y1,1);
    if (tmp_max>max) {
      max=tmp_max;
      max_x = x;
      max_y = int(y1);
    }
  }
  tmp_max=layerAbove.getAgastScore(x1,y1,1);
  if (tmp_max>max) {
    max=tmp_max;
    max_x = int(x1);
    max_y = int(y1);
  }

  //find dx/dy:
  register int s_0_0 = layerAbove.getAgastScore(max_x-1, max_y-1,1);
  register int s_1_0 = layerAbove.getAgastScore(max_x,   max_y-1,1);
  register int s_2_0 = layerAbove.getAgastScore(max_x+1, max_y-1,1);
  register int s_2_1 = layerAbove.getAgastScore(max_x+1, max_y,1);
  register int s_1_1 = layerAbove.getAgastScore(max_x,   max_y,1);
  register int s_0_1 = layerAbove.getAgastScore(max_x-1, max_y,1);
  register int s_0_2 = layerAbove.getAgastScore(max_x-1, max_y+1,1);
  register int s_1_2 = layerAbove.getAgastScore(max_x,   max_y+1,1);
  register int s_2_2 = layerAbove.getAgastScore(max_x+1, max_y+1,1);
  float dx_1, dy_1;
  float refined_max=subpixel2D(s_0_0, s_0_1,  s_0_2,
                               s_1_0, s_1_1, s_1_2,
                               s_2_0, s_2_1, s_2_2,
                               dx_1, dy_1);

  // calculate dx/dy in above coordinates
  float real_x = float(max_x)+dx_1;
  float real_y = float(max_y)+dy_1;
  bool returnrefined=true;
  if (layer%2==0) {
    dx=(real_x*6.0f+1.0f)/4.0f-float(x_layer);
    dy=(real_y*6.0f+1.0f)/4.0f-float(y_layer);
  } else {
    dx=(real_x*8.0+1.0)/6.0-float(x_layer);
    dy=(real_y*8.0+1.0)/6.0-float(y_layer);
  }

  // saturate
  if (dx>1.0f) {dx=1.0f;returnrefined=false;}
  if (dx<-1.0f) {dx=-1.0f;returnrefined=false;}
  if (dy>1.0f) {dy=1.0f;returnrefined=false;}
  if (dy<-1.0f) {dy=-1.0f;returnrefined=false;}

  // done and ok.
  ismax=true;
  if (returnrefined) {
    return std::max(refined_max,max);
  }
  return max;
}

inline float BriskScaleSpace::getScoreMaxBelow(const uint8_t layer,
                                               const int x_layer, const int y_layer,
                                               const int threshold, bool& ismax,
                                               float& dx, float& dy) {
  ismax=false;

  // relevant floating point coordinates
  float x_1;
  float x1;
  float y_1;
  float y1;

  if (layer%2==0) {
    // octave
    x_1=float(8*(x_layer)+1-4)/6.0;
    x1=float(8*(x_layer)+1+4)/6.0;
    y_1=float(8*(y_layer)+1-4)/6.0;
    y1=float(8*(y_layer)+1+4)/6.0;
  } else {
    x_1=float(6*(x_layer)+1-3)/4.0;
    x1=float(6*(x_layer)+1+3)/4.0;
    y_1=float(6*(y_layer)+1-3)/4.0;
    y1=float(6*(y_layer)+1+3)/4.0;
  }

  // the layer below
  assert(layer>0);
  BriskLayer& layerBelow=pyramid_[layer-1];

  // check the first row
  int max_x = x_1+1;
  int max_y = y_1+1;
  float tmp_max;
  float max=layerBelow.getAgastScore(x_1,y_1,1);
  if (max>threshold) return 0;
  for (int x=x_1+1; x<=int(x1); x++) {
    tmp_max=layerBelow.getAgastScore(float(x),y_1,1);
    if (tmp_max>threshold) return 0;
    if (tmp_max>max) {
      max=tmp_max;
      max_x = x;
    }
  }
  tmp_max=layerBelow.getAgastScore(x1,y_1,1);
  if (tmp_max>threshold) return 0;
  if (tmp_max>max) {
    max=tmp_max;
    max_x = int(x1);
  }

  // middle rows
  for (int y=y_1+1; y<=int(y1); y++) {
    tmp_max=layerBelow.getAgastScore(x_1,float(y),1);
    if (tmp_max>threshold) return 0;
    if (tmp_max>max) {
      max=tmp_max;
      max_x = int(x_1+1);
      max_y = y;
    }
    for (int x=x_1+1; x<=int(x1); x++) {
      tmp_max=layerBelow.getAgastScore(x,y,1);
      if (tmp_max>threshold) return 0;
      if (tmp_max==max) {
        const int t1=2*(
            layerBelow.getAgastScore(x-1,y,1)
            +layerBelow.getAgastScore(x+1,y,1)
            +layerBelow.getAgastScore(x,y+1,1)
            +layerBelow.getAgastScore(x,y-1,1))
                     +(layerBelow.getAgastScore(x+1,y+1,1)
                       +layerBelow.getAgastScore(x-1,y+1,1)
                       +layerBelow.getAgastScore(x+1,y-1,1)
                       +layerBelow.getAgastScore(x-1,y-1,1));
        const int t2=2*(
            layerBelow.getAgastScore(max_x-1,max_y,1)
            +layerBelow.getAgastScore(max_x+1,max_y,1)
            +layerBelow.getAgastScore(max_x,max_y+1,1)
            +layerBelow.getAgastScore(max_x,max_y-1,1))
                     +(layerBelow.getAgastScore(max_x+1,max_y+1,1)
                       +layerBelow.getAgastScore(max_x-1,max_y+1,1)
                       +layerBelow.getAgastScore(max_x+1,max_y-1,1)
                       +layerBelow.getAgastScore(max_x-1,max_y-1,1));
        if (t1>t2) {
          max_x = x;
          max_y = y;
        }
      }
      if (tmp_max>max) {
        max=tmp_max;
        max_x = x;
        max_y = y;
      }
    }
    tmp_max=layerBelow.getAgastScore(x1,float(y),1);
    if (tmp_max>threshold) return 0;
    if (tmp_max>max) {
      max=tmp_max;
      max_x = int(x1);
      max_y = y;
    }
  }

  // bottom row
  tmp_max=layerBelow.getAgastScore(x_1,y1,1);
  if (tmp_max>max) {
    max=tmp_max;
    max_x = int(x_1+1);
    max_y = int(y1);
  }
  for (int x=x_1+1; x<=int(x1); x++) {
    tmp_max=layerBelow.getAgastScore(float(x),y1,1);
    if (tmp_max>max) {
      max=tmp_max;
      max_x = x;
      max_y = int(y1);
    }
  }
  tmp_max=layerBelow.getAgastScore(x1,y1,1);
  if (tmp_max>max) {
    max=tmp_max;
    max_x = int(x1);
    max_y = int(y1);
  }

  //find dx/dy:
  register int s_0_0 = layerBelow.getAgastScore(max_x-1, max_y-1,1);
  register int s_1_0 = layerBelow.getAgastScore(max_x,   max_y-1,1);
  register int s_2_0 = layerBelow.getAgastScore(max_x+1, max_y-1,1);
  register int s_2_1 = layerBelow.getAgastScore(max_x+1, max_y,1);
  register int s_1_1 = layerBelow.getAgastScore(max_x,   max_y,1);
  register int s_0_1 = layerBelow.getAgastScore(max_x-1, max_y,1);
  register int s_0_2 = layerBelow.getAgastScore(max_x-1, max_y+1,1);
  register int s_1_2 = layerBelow.getAgastScore(max_x,   max_y+1,1);
  register int s_2_2 = layerBelow.getAgastScore(max_x+1, max_y+1,1);
  float dx_1, dy_1;
  float refined_max=subpixel2D(s_0_0, s_0_1,  s_0_2,
                               s_1_0, s_1_1, s_1_2,
                               s_2_0, s_2_1, s_2_2,
                               dx_1, dy_1);

  // calculate dx/dy in above coordinates
  float real_x = float(max_x)+dx_1;
  float real_y = float(max_y)+dy_1;
  bool returnrefined=true;
  if (layer%2==0) {
    dx=(real_x*6.0+1.0)/8.0-float(x_layer);
    dy=(real_y*6.0+1.0)/8.0-float(y_layer);
  } else {
    dx=(real_x*4.0-1.0)/6.0-float(x_layer);
    dy=(real_y*4.0-1.0)/6.0-float(y_layer);
  }

  // saturate
  if (dx>1.0) {dx=1.0;returnrefined=false;}
  if (dx<-1.0) {dx=-1.0;returnrefined=false;}
  if (dy>1.0) {dy=1.0;returnrefined=false;}
  if (dy<-1.0) {dy=-1.0;returnrefined=false;}

  // done and ok.
  ismax=true;
  if (returnrefined) {
    return std::max(refined_max,max);
  }
  return max;
}

inline float BriskScaleSpace::refine1D(const float s_05,
                                       const float s0, const float s05,
                                       float& max) {
  int i_05=int(1024.0*s_05+0.5);
  int i0=int(1024.0*s0+0.5);
  int i05=int(1024.0*s05+0.5);

  //   16.0000  -24.0000    8.0000
  //  -40.0000   54.0000  -14.0000
  //   24.0000  -27.0000    6.0000

  int three_a=16*i_05-24*i0+8*i05;
  // second derivative must be negative:
  if (three_a>=0) {
    if (s0>=s_05 && s0>=s05) {
      max=s0;
      return 1.0;
    }
    if (s_05>=s0 && s_05>=s05) {
      max=s_05;
      return 0.75;
    }
    if (s05>=s0 && s05>=s_05) {
      max=s05;
      return 1.5;
    }
  }

  int three_b=-40*i_05+54*i0-14*i05;
  // calculate max location:
  float ret_val=-float(three_b)/float(2*three_a);
  // saturate and return
  if (ret_val<0.75) ret_val= 0.75;
  else if (ret_val>1.5) ret_val= 1.5; // allow to be slightly off bounds ...?
  int three_c = +24*i_05  -27*i0    +6*i05;
  max=float(three_c)+float(three_a)*ret_val*ret_val+float(three_b)*ret_val;
  max/=3072.0;
  return ret_val;
}

inline float BriskScaleSpace::refine1D_1(const float s_05,
                                         const float s0, const float s05,
                                         float& max) {
  int i_05=int(1024.0*s_05+0.5);
  int i0=int(1024.0*s0+0.5);
  int i05=int(1024.0*s05+0.5);

  //  4.5000   -9.0000    4.5000
  //-10.5000   18.0000   -7.5000
  //  6.0000   -8.0000    3.0000

  int two_a=9*i_05-18*i0+9*i05;
  // second derivative must be negative:
  if (two_a>=0) {
    if (s0>=s_05 && s0>=s05) {
      max=s0;
      return 1.0;
    }
    if (s_05>=s0 && s_05>=s05) {
      max=s_05;
      return 0.6666666666666666666666666667;
    }
    if (s05>=s0 && s05>=s_05) {
      max=s05;
      return 1.3333333333333333333333333333;
    }
  }

  int two_b=-21*i_05+36*i0-15*i05;
  // calculate max location:
  float ret_val=-float(two_b)/float(2*two_a);
  // saturate and return
  if (ret_val<0.6666666666666666666666666667) ret_val= 0.666666666666666666666666667;
  else if (ret_val>1.33333333333333333333333333) ret_val= 1.333333333333333333333333333;
  int two_c = +12*i_05  -16*i0    +6*i05;
  max=float(two_c)+float(two_a)*ret_val*ret_val+float(two_b)*ret_val;
  max/=2048.0;
  return ret_val;
}

inline float BriskScaleSpace::refine1D_2(const float s_05,
                                         const float s0, const float s05,
                                         float& max) {
  int i_05=int(1024.0*s_05+0.5);
  int i0=int(1024.0*s0+0.5);
  int i05=int(1024.0*s05+0.5);

  //   18.0000  -30.0000   12.0000
  //  -45.0000   65.0000  -20.0000
  //   27.0000  -30.0000    8.0000

  int a=2*i_05-4*i0+2*i05;
  // second derivative must be negative:
  if (a>=0) {
    if (s0>=s_05 && s0>=s05) {
      max=s0;
      return 1.0;
    }
    if (s_05>=s0 && s_05>=s05) {
      max=s_05;
      return 0.7;
    }
    if (s05>=s0 && s05>=s_05) {
      max=s05;
      return 1.5;
    }
  }

  int b=-5*i_05+8*i0-3*i05;
  // calculate max location:
  float ret_val=-float(b)/float(2*a);
  // saturate and return
  if (ret_val<0.7) ret_val= 0.7;
  else if (ret_val>1.5) ret_val= 1.5; // allow to be slightly off bounds ...?
  int c = +3*i_05  -3*i0    +1*i05;
  max=float(c)+float(a)*ret_val*ret_val+float(b)*ret_val;
  max/=1024;
  return ret_val;
}

inline float BriskScaleSpace::subpixel2D(
    const int s_0_0, const int s_0_1, const int s_0_2,
    const int s_1_0, const int s_1_1, const int s_1_2,
    const int s_2_0, const int s_2_1, const int s_2_2,
    float& delta_x, float& delta_y) {

  // the coefficients of the 2d quadratic function least-squares fit:
  register int tmp1 =        s_0_0 + s_0_2 - 2*s_1_1 + s_2_0 + s_2_2;
  register int coeff1 = 3*(tmp1 + s_0_1 - ((s_1_0 + s_1_2)<<1) + s_2_1);
  register int coeff2 = 3*(tmp1 - ((s_0_1+ s_2_1)<<1) + s_1_0 + s_1_2 );
  register int tmp2 =                                  s_0_2 - s_2_0;
  register int tmp3 =                         (s_0_0 + tmp2 - s_2_2);
  register int tmp4 =                                   tmp3 -2*tmp2;
  register int coeff3 =                    -3*(tmp3 + s_0_1 - s_2_1);
  register int coeff4 =                    -3*(tmp4 + s_1_0 - s_1_2);
  register int coeff5 =            (s_0_0 - s_0_2 - s_2_0 + s_2_2)<<2;
  register int coeff6 = -(s_0_0  + s_0_2 - ((s_1_0 + s_0_1 + s_1_2 + s_2_1)<<1) -
                          5*s_1_1  + s_2_0  + s_2_2)<<1;


  // 2nd derivative test:
  register int H_det=4*coeff1*coeff2 - coeff5*coeff5;

  if (H_det==0) {
    delta_x=0.0;
    delta_y=0.0;
    return float(coeff6)/18.0;
  }

  if (!(H_det>0&&coeff1<0)) {
    // The maximum must be at the one of the 4 patch corners.
    int tmp_max=coeff3+coeff4+coeff5;
    delta_x=1.0; delta_y=1.0;

    int tmp = -coeff3+coeff4-coeff5;
    if (tmp>tmp_max) {
      tmp_max=tmp;
      delta_x=-1.0; delta_y=1.0;
    }
    tmp = coeff3-coeff4-coeff5;
    if (tmp>tmp_max) {
      tmp_max=tmp;
      delta_x=1.0; delta_y=-1.0;
    }
    tmp = -coeff3-coeff4+coeff5;
    if (tmp>tmp_max) {
      tmp_max=tmp;
      delta_x=-1.0; delta_y=-1.0;
    }
    return float(tmp_max+coeff1+coeff2+coeff6)/18.0;
  }

  // this is hopefully the normal outcome of the Hessian test
  delta_x=float(2*coeff2*coeff3 - coeff4*coeff5)/float(-H_det);
  delta_y=float(2*coeff1*coeff4 - coeff3*coeff5)/float(-H_det);
  // TODO: this is not correct, but easy, so perform a real boundary maximum search:
  bool tx=false; bool tx_=false; bool ty=false; bool ty_=false;
  if (delta_x>1.0) tx=true;
  else if (delta_x<-1.0) tx_=true;
  if (delta_y>1.0) ty=true;
  if (delta_y<-1.0) ty_=true;

  if (tx||tx_||ty||ty_) {
    // get two candidates:
    float delta_x1=0.0, delta_x2=0.0, delta_y1=0.0, delta_y2=0.0;
    if (tx) {
      delta_x1=1.0;
      delta_y1=-float(coeff4+coeff5)/float(2*coeff2);
      if (delta_y1>1.0) delta_y1=1.0; else if (delta_y1<-1.0) delta_y1=-1.0;
    } else if (tx_) {
      delta_x1=-1.0;
      delta_y1=-float(coeff4-coeff5)/float(2*coeff2);
      if (delta_y1>1.0) delta_y1=1.0; else if (delta_y1<-1.0) delta_y1=-1.0;
    }
    if (ty) {
      delta_y2=1.0;
      delta_x2=-float(coeff3+coeff5)/float(2*coeff1);
      if (delta_x2>1.0) delta_x2=1.0; else if (delta_x2<-1.0) delta_x2=-1.0;
    } else if (ty_) {
      delta_y2=-1.0;
      delta_x2=-float(coeff3-coeff5)/float(2*coeff1);
      if (delta_x2>1.0) delta_x2=1.0; else if (delta_x2<-1.0) delta_x2=-1.0;
    }
    // insert both options for evaluation which to pick
    float max1 = (coeff1*delta_x1*delta_x1+coeff2*delta_y1*delta_y1
                  +coeff3*delta_x1+coeff4*delta_y1
                  +coeff5*delta_x1*delta_y1
                  +coeff6)/18.0;
    float max2 = (coeff1*delta_x2*delta_x2+coeff2*delta_y2*delta_y2
                  +coeff3*delta_x2+coeff4*delta_y2
                  +coeff5*delta_x2*delta_y2
                  +coeff6)/18.0;
    if (max1>max2) {
      delta_x=delta_x1;
      delta_y=delta_x1;
      return max1;
    } else {
      delta_x=delta_x2;
      delta_y=delta_x2;
      return max2;
    }
  }

  // this is the case of the maximum inside the boundaries:
  return (coeff1*delta_x*delta_x+coeff2*delta_y*delta_y
          +coeff3*delta_x+coeff4*delta_y
          +coeff5*delta_x*delta_y
          +coeff6)/18.0;
}

// construct a layer
BriskLayer::BriskLayer(const Image<unsigned char>& img, float scale, float offset) {
  img_=img;
  scores_= Image<unsigned char>(img.Rows(), img.Cols(), 0.0);
  // attention: this means that the passed image reference must point to
  // persistent memory
  scale_=scale;
  offset_=offset;
  // create an agast detector
  oastDetector_.reset(new agast::OastDetector9_16(img.Cols(), img.Rows(), 0));
  agastDetector_5_8_.reset(new agast::AgastDetector5_8(img.Cols(), img.Rows(), 0));
}
// derive a layer
BriskLayer::BriskLayer(const BriskLayer& layer, int mode) {
  if (mode==CommonParams::HALFSAMPLE) {
    img_ = Image<unsigned char>(layer.img().Rows()/2, layer.img().Cols()/2);
    // TODO(cmsweeney): change this to CVD?
    halfsample(layer.img(), img_);
    scale_= layer.scale()*2;
    offset_=0.5*scale_-0.5;
  } else {
    img_ = Image<unsigned char>(2*(layer.img().Rows()/3), 2*(layer.img().Cols()/3));
    // TODO(cmsweeney): chagne this to CVD?
    twothirdsample(layer.img(), img_);
    scale_= layer.scale()*1.5;
    offset_=0.5*scale_-0.5;
  }
  scores_=Image<unsigned char>(img_.Rows(), img_.Cols(), 0.0);
  oastDetector_.reset(new agast::OastDetector9_16(img_.Cols(), img_.Rows(), 0));
  agastDetector_5_8_.reset(new agast::AgastDetector5_8(img_.Cols(), img_.Rows(), 0));
}

// Fast/Agast
// wraps the agast class
void BriskLayer::getAgastPoints(uint8_t threshold,
                                std::vector<CvPoint>& keypoints) {
  oastDetector_->set_threshold(threshold);
  oastDetector_->detect(img_.Data(),keypoints);

  // also write scores
  const int num=keypoints.size();
  const int imcols=img_.Cols();

  for (int i=0; i<num; i++) {
    const int offs=keypoints[i].x+keypoints[i].y*imcols;
    *(scores_.Data()+offs)=oastDetector_->cornerScore(img_.Data()+offs);
  }
}

inline uint8_t BriskLayer::getAgastScore(int x, int y, uint8_t threshold) {
  if (x<3||y<3) return 0;
  if (x>=img_.Cols()-3||y>=img_.Rows()-3) return 0;
  uint8_t& score=*(scores_.Data()+x+y*scores_.Cols());
  if (score>2) { return score; }
  oastDetector_->set_threshold(threshold-1);
  score = oastDetector_->cornerScore(img_.Data()+x+y*img_.Cols());
  if (score<threshold) score = 0;
  return score;
}

inline uint8_t BriskLayer::getAgastScore_5_8(int x, int y, uint8_t threshold) {
  if (x<2||y<2) return 0;
  if (x>=img_.Cols()-2||y>=img_.Rows()-2) return 0;
  agastDetector_5_8_->set_threshold(threshold-1);
  uint8_t score = agastDetector_5_8_->cornerScore(img_.Data()+x+y*img_.Cols());
  if (score<threshold) score = 0;
  return score;
}

inline uint8_t BriskLayer::getAgastScore(float xf, float yf, uint8_t threshold, float scale) {
  if (scale<=1.0f) {
    // just do an interpolation inside the layer
    const int x=int(xf);
    const float rx1=xf-float(x);
    const float rx=1.0f-rx1;
    const int y=int(yf);
    const float ry1=yf-float(y);
    const float ry=1.0f-ry1;

    return rx*ry*getAgastScore(x, y, threshold)+
        rx1*ry*getAgastScore(x+1, y, threshold)+
        rx*ry1*getAgastScore(x, y+1, threshold)+
        rx1*ry1*getAgastScore(x+1, y+1, threshold);
  } else {
    // this means we overlap area smoothing
    const float halfscale = scale/2.0f;
    // get the scores first:
    for (int x=int(xf-halfscale); x<=int(xf+halfscale+1.0f); x++) {
      for (int y=int(yf-halfscale); y<=int(yf+halfscale+1.0f); y++) {
        getAgastScore(x, y, threshold);
      }
    }
    // get the smoothed value
    return value(scores_,xf,yf,scale);
  }
}

// access gray values (smoothed/interpolated)
inline uint8_t BriskLayer::value(const Image<unsigned char>& mat,
                                 float xf, float yf, float scale) {
  // assert(!mat.empty());
  CHECK_GT(mat.Rows(), 0);
  CHECK_GT(mat.Cols(), 0);
  // get the position
  const int x = floor(xf);
  const int y = floor(yf);
  const Image<unsigned char>& image=mat;
  const int& imagecols=image.Cols();

  // get the sigma_half:
  const float sigma_half=scale/2;
  const float area=4.0*sigma_half*sigma_half;
  // calculate output:
  int ret_val;
  if (sigma_half<0.5) {
    //interpolation multipliers:
    const int r_x=(xf-x)*1024;
    const int r_y=(yf-y)*1024;
    const int r_x_1=(1024-r_x);
    const int r_y_1=(1024-r_y);
    const uchar* ptr=image.Data()+x+y*imagecols;
    // just interpolate:
    ret_val=(r_x_1*r_y_1*int(*ptr));
    ptr++;
    ret_val+=(r_x*r_y_1*int(*ptr));
    ptr+=imagecols;
    ret_val+=(r_x*r_y*int(*ptr));
    ptr--;
    ret_val+=(r_x_1*r_y*int(*ptr));
    return 0xFF&((ret_val+512)/1024/1024);
  }

  // this is the standard case (simple, not speed optimized yet):

  // scaling:
  const int scaling = 4194304.0/area;
  const int scaling2=float(scaling)*area/1024.0;

  // calculate borders
  const float x_1=xf-sigma_half;
  const float x1=xf+sigma_half;
  const float y_1=yf-sigma_half;
  const float y1=yf+sigma_half;

  const int x_left=int(x_1+0.5);
  const int y_top=int(y_1+0.5);
  const int x_right=int(x1+0.5);
  const int y_bottom=int(y1+0.5);

  // overlap area - multiplication factors:
  const float r_x_1=float(x_left)-x_1+0.5;
  const float r_y_1=float(y_top)-y_1+0.5;
  const float r_x1=x1-float(x_right)+0.5;
  const float r_y1=y1-float(y_bottom)+0.5;
  const int dx=x_right-x_left-1;
  const int dy=y_bottom-y_top-1;
  const int A=(r_x_1*r_y_1)*scaling;
  const int B=(r_x1*r_y_1)*scaling;
  const int C=(r_x1*r_y1)*scaling;
  const int D=(r_x_1*r_y1)*scaling;
  const int r_x_1_i=r_x_1*scaling;
  const int r_y_1_i=r_y_1*scaling;
  const int r_x1_i=r_x1*scaling;
  const int r_y1_i=r_y1*scaling;

  // now the calculation:
  const uchar* ptr=image.Data()+x_left+imagecols*y_top;
  // first row:
  ret_val=A*int(*ptr);
  ptr++;
  const uchar* end1 = ptr+dx;
  for (; ptr<end1; ptr++) {
    ret_val+=r_y_1_i*int(*ptr);
  }
  ret_val+=B*int(*ptr);
  // middle ones:
  ptr+=imagecols-dx-1;
  const uchar* end_j=ptr+dy*imagecols;
  for (; ptr<end_j; ptr+=imagecols-dx-1) {
    ret_val+=r_x_1_i*int(*ptr);
    ptr++;
    const uchar* end2 = ptr+dx;
    for (; ptr<end2; ptr++) {
      ret_val+=int(*ptr)*scaling;
    }
    ret_val+=r_x1_i*int(*ptr);
  }
  // last row:
  ret_val+=D*int(*ptr);
  ptr++;
  const uchar* end3 = ptr+dx;
  for (; ptr<end3; ptr++) {
    ret_val+=r_y1_i*int(*ptr);
  }
  ret_val+=C*int(*ptr);

  return 0xFF&((ret_val+scaling2/2)/scaling2/1024);
}

// half sampling
inline void BriskLayer::halfsample(const Image<unsigned char>& srcimg,
                                   Image<unsigned char>& dstimg) {
  const unsigned short leftoverCols = ((srcimg.Cols()%16)/2);// take care with border...
  const bool noleftover = (srcimg.Cols()%16)==0; // note: leftoverCols can be zero but this still false...

  // make sure the destination image is of the right size:
  CHECK_EQ(srcimg.Cols()/2, dstimg.Cols());
  CHECK_EQ(srcimg.Rows()/2, dstimg.Rows());

  #ifndef THEIA_USE_SSE
  srcimg.HalfSample(&dstimg);
  #else
  // mask needed later:
  register __m128i mask = _mm_set_epi32 (0x00FF00FF, 0x00FF00FF, 0x00FF00FF, 0x00FF00FF);
  // to be added in order to make successive averaging correct:
  register __m128i ones = _mm_set_epi32 (0x11111111, 0x11111111, 0x11111111, 0x11111111);

  // data pointers:
  __m128i* p1=(__m128i*)srcimg.Data();
  __m128i* p2=(__m128i*)(srcimg.Data()+srcimg.Cols());
  __m128i* p_dest=(__m128i*)dstimg.Data();
  unsigned char* p_dest_char;//=(unsigned char*)p_dest;

  // size:
  const unsigned int size = (srcimg.Cols()*srcimg.Rows())/16;
  const unsigned int hsize = srcimg.Cols()/16;
  __m128i* p_end=p1+size;
  unsigned int row=0;
  const unsigned int end=hsize/2;
  bool half_end;
  if (hsize%2==0)
    half_end=false;
  else
    half_end=true;
  while(p2<p_end) {
    for (unsigned int i=0; i<end;i++) {
      // load the two blocks of memory:
      __m128i upper;
      __m128i lower;
      if (noleftover) {
        upper=_mm_load_si128(p1);
        lower=_mm_load_si128(p2);
      } else {
        upper=_mm_loadu_si128(p1);
        lower=_mm_loadu_si128(p2);
      }

      __m128i result1=_mm_adds_epu8 (upper, ones);
      result1=_mm_avg_epu8 (upper, lower);

      // increment the pointers:
      p1++;
      p2++;

      // load the two blocks of memory:
      upper=_mm_loadu_si128(p1);
      lower=_mm_loadu_si128(p2);
      __m128i result2=_mm_adds_epu8 (upper, ones);
      result2=_mm_avg_epu8 (upper, lower);
      // calculate the shifted versions:
      __m128i result1_shifted = _mm_srli_si128 (result1, 1);
      __m128i result2_shifted = _mm_srli_si128 (result2, 1);
      // pack:
      __m128i result=_mm_packus_epi16 (_mm_and_si128 (result1, mask),
                                       _mm_and_si128 (result2, mask));
      __m128i result_shifted = _mm_packus_epi16 (_mm_and_si128 (result1_shifted, mask),
                                                 _mm_and_si128 (result2_shifted, mask));
      // average for the second time:
      result=_mm_avg_epu8(result,result_shifted);

      // store to memory
      _mm_storeu_si128 (p_dest, result);

      // increment the pointers:
      p1++;
      p2++;
      p_dest++;
      //p_dest_char=(unsigned char*)p_dest;
    }
    // if we are not at the end of the row, do the rest:
    if (half_end) {
      // load the two blocks of memory:
      __m128i upper;
      __m128i lower;
      if (noleftover) {
        upper=_mm_load_si128(p1);
        lower=_mm_load_si128(p2);
      } else {
        upper=_mm_loadu_si128(p1);
        lower=_mm_loadu_si128(p2);
      }

      __m128i result1=_mm_adds_epu8 (upper, ones);
      result1=_mm_avg_epu8 (upper, lower);

      // increment the pointers:
      p1++;
      p2++;

      // compute horizontal pairwise average and store
      p_dest_char=(unsigned char*)p_dest;
      const UCHAR_ALIAS* result=(UCHAR_ALIAS*)&result1;
      for (unsigned int j=0; j<8; j++) {
        *(p_dest_char++)=(*(result+2*j)+*(result+2*j+1))/2;
      }
      //p_dest_char=(unsigned char*)p_dest;
    } else {
      p_dest_char=(unsigned char*)p_dest;
    }

    if (noleftover) {
      row++;
      p_dest=(__m128i*)(dstimg.Data()+row*dstimg.Cols());
      p1=(__m128i*)(srcimg.Data()+2*row*srcimg.Cols());
      //p2=(__m128i*)(srcimg.Data()+(2*row+1)*srcimg.Cols());
      //p1+=hsize;
      p2=p1+hsize;
    } else {
      const unsigned char* p1_src_char=(unsigned char*)(p1);
      const unsigned char* p2_src_char=(unsigned char*)(p2);
      for (unsigned int k=0; k<leftoverCols; k++) {
        unsigned short tmp = p1_src_char[k]+p1_src_char[k+1]+
                             p2_src_char[k]+p2_src_char[k+1];
        *(p_dest_char++)=(unsigned char)(tmp/4);
      }
      // done with the two rows:
      row++;
      p_dest=(__m128i*)(dstimg.Data()+row*dstimg.Cols());
      p1=(__m128i*)(srcimg.Data()+2*row*srcimg.Cols());
      p2=(__m128i*)(srcimg.Data()+(2*row+1)*srcimg.Cols());
    }
  }
#endif  // THEIA_USE_SSE
}

inline void BriskLayer::twothirdsample(const Image<unsigned char>& srcimg,
                                       Image<unsigned char>& dstimg) {
  const unsigned short leftoverCols = ((srcimg.Cols()/3)*3)%15;// take care with border...

  // make sure the destination image is of the right size:
  CHECK_EQ((srcimg.Cols()/3)*2, dstimg.Cols());
  CHECK_EQ((srcimg.Rows()/3)*2, dstimg.Rows());

  #ifndef THEIA_USE_SSE
  // CVD two thirds sample.
  srcimg.TwoThirdsSample(&dstimg);
  #else
  
  // masks:
  register __m128i mask1 = _mm_set_epi8 (0x80,0x80,0x80,0x80,0x80,0x80,0x80,12,0x80,10,0x80,7,0x80,4,0x80,1);
  register __m128i mask2 = _mm_set_epi8 (0x80,0x80,0x80,0x80,0x80,0x80,12,0x80,10,0x80,7,0x80,4,0x80,1,0x80);
  register __m128i mask = _mm_set_epi8 (0x80,0x80,0x80,0x80,0x80,0x80,14,12,11,9,8,6,5,3,2,0);
  register __m128i store_mask = _mm_set_epi8 (0,0,0,0,0,0,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80);

  // data pointers:
  const unsigned char* p1=srcimg.Data();
  const unsigned char* p2=p1+srcimg.Cols();
  const unsigned char* p3=p2+srcimg.Cols();
  unsigned char* p_dest1 = dstimg.Data();
  unsigned char* p_dest2 = p_dest1+dstimg.Cols();
  const unsigned char* p_end=p1+(srcimg.Cols()*srcimg.Rows());

  unsigned int row=0;
  unsigned int row_dest=0;
  int hsize = srcimg.Cols()/15;
  while(p3<p_end) {
    for (int i=0; i<hsize; i++) {
      // load three rows
      __m128i first = _mm_loadu_si128((__m128i*)p1);
      __m128i second = _mm_loadu_si128((__m128i*)p2);
      __m128i third = _mm_loadu_si128((__m128i*)p3);

      // upper row:
      __m128i upper = _mm_avg_epu8(_mm_avg_epu8(first,second),first);
      __m128i temp1_upper = _mm_or_si128(_mm_shuffle_epi8(upper,mask1),_mm_shuffle_epi8(upper,mask2));
      __m128i temp2_upper=_mm_shuffle_epi8(upper,mask);
      __m128i result_upper = _mm_avg_epu8(_mm_avg_epu8(temp2_upper,temp1_upper),temp2_upper);

      // lower row:
      __m128i lower = _mm_avg_epu8(_mm_avg_epu8(third,second),third);
      __m128i temp1_lower = _mm_or_si128(_mm_shuffle_epi8(lower,mask1),_mm_shuffle_epi8(lower,mask2));
      __m128i temp2_lower=_mm_shuffle_epi8(lower,mask);
      __m128i result_lower = _mm_avg_epu8(_mm_avg_epu8(temp2_lower,temp1_lower),temp2_lower);

      // store:
      if (i*10+16>dstimg.Cols()) {
        _mm_maskmoveu_si128(result_upper, store_mask, (char*)p_dest1);
        _mm_maskmoveu_si128(result_lower, store_mask, (char*)p_dest2);
      } else {
        _mm_storeu_si128 ((__m128i*)p_dest1, result_upper);
        _mm_storeu_si128 ((__m128i*)p_dest2, result_lower);
      }

      // shift pointers:
      p1+=15;
      p2+=15;
      p3+=15;
      p_dest1+=10;
      p_dest2+=10;
    }

    // fill the remainder:
    for (unsigned int j = 0; j<leftoverCols;j+=3) {
      const unsigned short A1=*(p1++);
      const unsigned short A2=*(p1++);
      const unsigned short A3=*(p1++);
      const unsigned short B1=*(p2++);
      const unsigned short B2=*(p2++);
      const unsigned short B3=*(p2++);
      const unsigned short C1=*(p3++);
      const unsigned short C2=*(p3++);
      const unsigned short C3=*(p3++);

      *(p_dest1++)=(unsigned char)(((4*A1+2*(A2+B1)+B2)/9)&0x00FF);
      *(p_dest1++)=(unsigned char)(((4*A3+2*(A2+B3)+B2)/9)&0x00FF);
      *(p_dest2++)=(unsigned char)(((4*C1+2*(C2+B1)+B2)/9)&0x00FF);
      *(p_dest2++)=(unsigned char)(((4*C3+2*(C2+B3)+B2)/9)&0x00FF);
    }


    // increment row counter:
    row+=3;
    row_dest+=2;

    // reset pointers
    p1=srcimg.Data()+row*srcimg.Cols();
    p2=p1+srcimg.Cols();
    p3=p2+srcimg.Cols();
    p_dest1 = dstimg.Data()+row_dest*dstimg.Cols();
    p_dest2 = p_dest1+dstimg.Cols();
  }
#endif  // THEIA_USE_SSE
}
}  // namespace theia
