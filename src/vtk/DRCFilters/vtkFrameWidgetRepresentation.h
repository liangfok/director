/*=========================================================================

Program:   Visualization Toolkit

Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
All rights reserved.
See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkFrameWidgetRepresentation - An orthonormal frame representation
// .SECTION Description
// An orthonormal frame representation for use with the vtkFrameWidget

// .SECTION See Also
// vtkFrameWidget vtkFrameWidget


#ifndef __vtkFrameWidgetRepresentation_h
#define __vtkFrameWidgetRepresentation_h

#include "vtkWidgetRepresentation.h"

#include <vtkDRCFiltersModule.h>

class vtkTransform;
class vtkDataSet;

class VTKDRCFILTERS_EXPORT vtkFrameWidgetRepresentation : public vtkWidgetRepresentation
{
public:
  // Description:
  // Instantiate the class.
  static vtkFrameWidgetRepresentation *New();

  // Description:
  // Standard methods for the class.
  vtkTypeMacro(vtkFrameWidgetRepresentation,vtkWidgetRepresentation);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Return the transform describing the frame.  Changes to this transform
  // will be reflected in the rendered axes.
  vtkTransform* GetTransform();

  // Description:
  // Set the transform describing the frame.  Note that this method does not
  // copy the transform, rather it increments the transforms reference count
  // and uses it directly.  As a side effect of using the transform directly
  // it will set PostMultiply to true on the transform.  This method calls
  // vtkProp3D::SetUserTransform(t) on its internal vtkAxesActor.
  virtual void SetTransform(vtkTransform* t);

  // Description:
  // These are methods that satisfy vtkWidgetRepresentation's API.
  virtual void BuildRepresentation();
  virtual int ComputeInteractionState(int X, int Y, int modify=0);
  virtual void StartWidgetInteraction(double e[2]);
  virtual void WidgetInteraction(double e[2]);

  virtual void OnMouseHover(double e[2]);
  virtual void HighlightOff();
  virtual void HighlightActor(vtkDataSet* dataset);

  virtual double *GetBounds();
  
  // Description:
  // Methods supporting, and required by, the rendering process.
  virtual void ReleaseGraphicsResources(vtkWindow*);
  virtual int RenderOpaqueGeometry(vtkViewport*);
  virtual int RenderOverlay(vtkViewport*);
  virtual int RenderTranslucentPolygonalGeometry(vtkViewport*);
  virtual int HasTranslucentPolygonalGeometry();

  // Description:
  // The interaction state may be set from a widget (e.g., vtkBoxWidget2) or
  // other object. This controls how the interaction with the widget
  // proceeds. Normally this method is used as part of a handshaking
  // process with the widget: First ComputeInteractionState() is invoked that
  // returns a state based on geometric considerations (i.e., cursor near a
  // widget feature), then based on events, the widget may modify this
  // further.
  void SetInteractionState(int state);

  // Description:
  // Set the size of the axes in world coordinates.
  vtkSetMacro(WorldSize, double);
  vtkGetMacro(WorldSize, double);

  enum {Outside=0,Translating,TranslatingInPlane,Rotating};

protected:
  vtkFrameWidgetRepresentation();
  ~vtkFrameWidgetRepresentation();

  double WorldSize;


  // Manage how the representation appears
  double LastEventPosition[3];

  // Helper methods
  virtual void Translate(double *p1, double *p2);
  virtual void TranslateInPlane(double *p1, double *p2);
  virtual void Rotate(int X, int Y, double *p1, double *p2, double *vpn);

private:

  class vtkInternal;
  vtkInternal* Internal;

  vtkFrameWidgetRepresentation(const vtkFrameWidgetRepresentation&);  //Not implemented
  void operator=(const vtkFrameWidgetRepresentation&);  //Not implemented
};

#endif