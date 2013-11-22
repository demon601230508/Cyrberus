/**********************************************************************************
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 */
//--------------------------------------------------------------------------------//

#ifndef GUI_ENVELOPE
#define GUI_ENVELOPE

#include "ofxUIWidgetWithLabel.h"
#include "Envelope.h"

class GuiEnvelope : public ofxUIWidgetWithLabel {
    
public:
    
    /* Constructor */
    
    GuiEnvelope(string _name, ofVec2f _value,
                float w, float h, float x = 0,
                float y = 0) : ofxUIWidgetWithLabel()
    {
        init(_name, _value, w, h, x, y);
    }
    
    
    /* Functions */
    
    //----------------------------------------------------------------------------//
    // INITIALISE ENVELOPE EDITOR
    //----------------------------------------------------------------------------//
    
    void init(string _name, ofVec2f _value,
              float w, float h, float x = 0, float y = 0)
    {
        
        rect = new ofxUIRectangle(x,y,w,h);
		name = string(_name);
		kind = OFX_UI_WIDGET_2DPAD;
		paddedRect = new ofxUIRectangle(-padding, -padding,
                                        w+padding*2.0, h+padding);
		paddedRect->setParent(rect);
        draw_fill = true;
        draw_outline = true;
        value = _value;         //the widget's value
        
		labelPrecision = 2;
		
		if(value.x > 1)
		{
			value.x = 1;
		}
		else if(value.x < 0)
		{
			value.x = 0;
		}
		
		if(value.y > 1)
		{
			value.y = 1;
		}
		else if(value.y < 0)
		{
			value.y = 0;
		}
		
		label = new ofxUILabel(0,h+padding,(name+" LABEL"),
                               (name + ": " + ofxUIToString(value.x,labelPrecision)
                                + ", " + ofxUIToString(value.y,labelPrecision)),
                               OFX_UI_FONT_SMALL);
		label->setParent(label);
		label->setRectParent(rect);
        label->setEmbedded(true);
        
        return;
        
    }
    
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
    
    virtual void update()
    {

    }

    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
    
    virtual void setDrawPadding(bool _draw_padded_rect)
	{
		draw_padded_rect = _draw_padded_rect;
        label->setDrawPadding(false);
	}
    
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
    
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline)
	{
		draw_padded_rect_outline = _draw_padded_rect_outline;
        label->setDrawPaddingOutline(false);
	}
    
    //----------------------------------------------------------------------------//
    // DRAW FILL
    //----------------------------------------------------------------------------//
    
    virtual void drawFill()
    {
        if(draw_fill)
        {
            ofxUIFill();
            
            ofxUISetColor(color_fill);
			
            ofxUISetRectMode(OFX_UI_RECTMODE_CENTER);
			
            ofxUIDrawRect(rect->getX() + value.x * rect->getWidth(),
                          rect->getY() + value.y * rect->getHeight(),
                          OFX_UI_GLOBAL_WIDGET_SPACING,
                          OFX_UI_GLOBAL_WIDGET_SPACING);
			
            ofxUISetRectMode(OFX_UI_RECTMODE_CORNER);
            
            /*** Draw envelope to box here ***/
            
            if (isFrequency == true) {
                drawFrequencyEnvelope(*envelope);
            }
            else if (isFrequency == false) {
                drawEnvelope(*envelope);
            }
            
            /* Crosshair */
            
			ofxUIDrawLine(rect->getX() + value.x * rect->getWidth(),
                          rect->getY(),
                          rect->getX() + value.x * rect->getWidth(),
                          rect->getY() + rect->getHeight());
			
            ofxUIDrawLine(rect->getX(),
                          rect->getY() + value.y * rect->getHeight(),
                          rect->getX() + rect->getWidth(),
                          rect->getY() + value.y * rect->getHeight());
        }
    }
    
    //----------------------------------------------------------------------------//
    // DRAW FILL HIGHLIGHT
    //----------------------------------------------------------------------------//
    
    virtual void drawFillHighlight()
    {
        if(draw_fill_highlight)
        {
            ofxUIFill();
            
            ofxUISetColor(color_fill_highlight);
            
			ofxUISetRectMode(OFX_UI_RECTMODE_CENTER);
            
			ofxUIDrawRect(rect->getX() + value.x * rect->getWidth(),
                          rect->getY() + value.y * rect->getHeight(),
                          OFX_UI_GLOBAL_WIDGET_SPACING,
                          OFX_UI_GLOBAL_WIDGET_SPACING);
			
            ofxUISetRectMode(OFX_UI_RECTMODE_CORNER);
			
            /* Crosshair Highlight */
            
			ofxUIDrawLine(rect->getX() + value.x * rect->getWidth(),
                          rect->getY(),
                          rect->getX() + value.x * rect->getWidth(),
                          rect->getY() + rect->getHeight());
            
			ofxUIDrawLine(rect->getX(),
                          rect->getY() + value.y * rect->getHeight(),
                          rect->getX() + rect->getWidth(),
                          rect->getY() + value.y * rect->getHeight());
			
            /* Crosshair label */
            
			label->drawString(rect->getX() + value.x * rect->getWidth()
                              + OFX_UI_GLOBAL_WIDGET_SPACING,
                              rect->getY() + value.y * rect->getHeight(),
                              "(" + ofxUIToString(value.x,labelPrecision)
                              + ", " + ofxUIToString((1-value.y), labelPrecision)
                              + ")");
        }
    }
    
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
    
    
    void mouseMoved(int x, int y )
    {
        if(rect->inside(x, y))
        {
            state = OFX_UI_STATE_OVER;
        }
        else
        {
            state = OFX_UI_STATE_NORMAL;
        }
        stateChange();
    }
    
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
    
    void mouseDragged(int x, int y, int button)
    {
        if(hit)
        {
            state = OFX_UI_STATE_DOWN;
			input(x, y);
            
            moveGrabbedPoint();
            moveGrabbedCurve();
            
			triggerEvent(this);
        }
        else
        {
            state = OFX_UI_STATE_NORMAL;
        }
        stateChange();
    }
    
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
    
    void mousePressed(int x, int y, int button)
    {
        if(rect->inside(x, y))
        {
            /* For Left Clicks */
            if (button == 0) {
                isRightClick = false;
            }
            else if (button == 2) {
                isRightClick = true;
            }
            
            hit = true;
            state = OFX_UI_STATE_DOWN;
            input(x, y);
            
            checkForPointNode();
            triggerEvent(this);
            
        }
        else
        {
            state = OFX_UI_STATE_NORMAL;
        }
        stateChange();
    }
    
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
    
    void mouseReleased(int x, int y, int button)
    {
        //cout << "mouse released x="<< x << endl;
        if(hit)
        {
#ifdef TARGET_OPENGLES
            state = OFX_UI_STATE_NORMAL;
#else
            state = OFX_UI_STATE_OVER;
#endif
            
			input(x, y);
            
            if (isPointGrabbed==true) {
                isPointGrabbed = false;
            }
            else if (isCurveGrabbed==true) {
                isCurveGrabbed = false;
            }
            else if (isRightClick==true) {
                isRightClick = false;
            }
            else{
                addEnvelopePoint();
            }
            
			triggerEvent(this);
        }
        else
        {
            state = OFX_UI_STATE_NORMAL;
        }
        stateCheck = abs(stateCheck - 1);
        stateChange();
        hit = false;
    }
    
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
	
    void keyPressed(int key)
    {
		if(state == OFX_UI_STATE_OVER)
		{
			switch (key)
			{
				case OF_KEY_RIGHT:
                {
                    value.x+= 0.01f;
                    updateLabel();
                    triggerEvent(this);
                }
					break;
					
				case OF_KEY_UP:
                {
                    value.y += 0.01f;
                    updateLabel();
                    triggerEvent(this);
                }
					break;
					
				case OF_KEY_LEFT:
                {
                    value.x -= 0.01f;
                    updateLabel();
                    triggerEvent(this);
                }
					break;
					
				case OF_KEY_DOWN:
                {
                    value.y -= 0.01f;
                    updateLabel();
                    triggerEvent(this);
                }
					break;
					
				default:
					break;
			}
		}
    }
    
    //----------------------------------------------------------------------------//
    //----------------------------------------------------------------------------//
    
    void keyReleased(int key)
    {
		
    }
    
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
    
    void windowResized(int w, int h)
    {
		
    }
    
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
    
	void input(float x, float y)
	{
        
		value.x = rect->percentInside(x, y).x;
		value.y = rect->percentInside(x, y).y;
        if(value.x > 1.0)
        {
            value.x = 1.0;
        }
        else if(value.x < 0.0)
        {
            value.x = 0.0;
        }
        
        if(value.y > 1.0)
        {
            value.y = 1.0;
        }
        else if(value.y < 0.0)
        {
            value.y = 0.0;
        }
        
        /* Convert to "Frequency Input" if isFrequency == true (this is converted
         back to original for display) */
        if (isFrequency == true) {
            value.y = toFrequency(value.y);
        }
        
		updateLabel();
        
	}
	
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
    
	void updateLabel()
	{
        //string str;
        
        //for (int i=0; i<envelope.points.size(); i++) {
          //  str += "(" + ofToString(envelope.points.at(i).time) + " - "
          //  + ofToString(envelope.points.at(i).value) + ") ";
        //}
        
		label->setLabel(name + ": " + ofxUIToString(value.x,labelPrecision)
                        + ", " + ofxUIToString((1-value.y),labelPrecision) );
	}
	
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
    
    void stateChange()
    {
        switch (state) {
            case OFX_UI_STATE_NORMAL:
            {
                draw_fill_highlight = false;
                draw_outline_highlight = false;
				label->unfocus();
            }
                break;
            case OFX_UI_STATE_OVER:
            {
                draw_fill_highlight = false;
                draw_outline_highlight = true;
				label->unfocus();
            }
                break;
            case OFX_UI_STATE_DOWN:
            {
                draw_fill_highlight = true;
                draw_outline_highlight = true;
				label->focus();
            }
                break;
            case OFX_UI_STATE_SUSTAINED:
            {
                draw_fill_highlight = false;
                draw_outline_highlight = false;
				label->unfocus();
            }
                break;
                
            default:
                break;
        }
    }
    
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
	
    void setVisible(bool _visible)
    {
        visible = _visible;
        label->setVisible(visible);
    }
    
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
    
	void setValue(ofVec2f _value)
	{
		if(_value.x > rangeX.y)
		{
			_value.x = rangeX.y;
		}
		else if(_value.x < rangeX.x)
		{
			_value.x = rangeX.x;
		}
		
		if(_value.y > rangeY.y)
		{
			_value.y = rangeY.y;
		}
		else if(_value.y < rangeY.x)
		{
			_value.y = rangeY.x;
		}
        
		updateLabel();
	}
    
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
	
	ofVec2f getValue()
	{
		return value;
	}
    
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
	
	ofVec2f getPercentValue()
	{
		return value;
	}
    
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
    
	ofxUILabel *getLabel()
	{
		return label;
	}
	
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
    
	void setParent(ofxUIWidget *_parent)
	{
		parent = _parent;
        label->getRect()->setY(rect->getHeight()+padding);
        paddedRect->height += label->getPaddingRect()->height+padding;
	}
    
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
    
    bool isDraggable()
    {
        return true;
    }
    
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
    
    void setLabelPrecision(int _precision)
    {
        labelPrecision = _precision;
        updateLabel();
    }
    
    //----------------------------------------------------------------------------//
    // ADD POINT AT X - Y
    //----------------------------------------------------------------------------//
    
    void addEnvelopePoint(){
        
        envelope->addPoint(value.x, 1.0f-value.y);
        
        return;
        
    }
    
    //----------------------------------------------------------------------------//
    // TAKE ENVELOPE
    //----------------------------------------------------------------------------//
    
    void setupEnvelope(Envelope *_envelope)
    {
        
        envelope = _envelope;
        
        return;
        
    }
    
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
    
    
    
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
    
    /* Public Variables */
    
    bool isFrequency = false;
    bool isPointGrabbed = false;
    bool isCurveGrabbed = false;
    bool isRightClick = false;
    
    float pointNodeRadius = 5.0f;
    float pointNodeRectWidth = 6.0f;
    float pointNodeRectHeight = 6.0f;
    
    Envelope *envelope;
    Pt *grabbedPoint;
    Pt *nextPoint;
    bool stateCheck;

    
//--------------------------------------------------------------------------------//
// PROTECTED CLASS STUFF
//--------------------------------------------------------------------------------//
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent;
	ofVec2f value;
    int labelPrecision;
    ofVec2f rangeX, rangeY;
    
    //----------------------------------------------------------------------------//
    // DRAW ENVELOPE
    //----------------------------------------------------------------------------//
    
    void drawEnvelope(Envelope tempEnv){
        
        float envPosX = rect->getX();
        float envPosY = rect->getY() + rect->getHeight();
        
        float prevX = envPosX;
        float prevY = envPosY
        + (1-tempEnv.getValue((float)0.0f/rect->getWidth())
           * rect->getHeight());
        float currentX, currentY, nextX, nextY, halfwayBetweenX;
        
        /* Draw Envelope */
        for (int i=0; i < rect->getWidth(); i++) {
            
            currentX = envPosX + i;
            currentY = envPosY
            + (1-tempEnv.getValue((double)i/rect->getWidth()) * rect->getHeight());
            
            ofCircle(currentX, currentY, 1.0f);
            
            ofxUIDrawLine(prevX, prevY, currentX, currentY);
            
            prevX = currentX;
            prevY = currentY;
            
        }
        
        for (int i=0; i < tempEnv.points.size()-1 && 1 < tempEnv.points.size();
             i++)
        {
            
            currentX = envPosX
            + tempEnv.points.at(i).time *rect->getWidth();
            currentY = rect->getY()
            + (1 - tempEnv.points.at(i).value) *rect->getHeight();
            
            nextX = envPosX
            + tempEnv.points.at(i+1).time *rect->getWidth();
            nextY = rect->getY()
            + (1 - tempEnv.points.at(i+1).value) *rect->getHeight();
            
            halfwayBetweenX = (currentX+nextX)/2;
            
            /* Draw Points */
            ofCircle(currentX, currentY, 5.0f);
            
            /* Draw Bezier Curve Control Squares */
            ofxUIDrawRect(halfwayBetweenX
                    - (pointNodeRectWidth/2),
                    envPosY
                    + 1
                    - tempEnv.getValue((halfwayBetweenX-envPosX)/rect->getWidth())
                    * rect->getHeight()
                    - (pointNodeRectHeight/2),
                          pointNodeRectWidth,
                          pointNodeRectHeight);
            
        }
        
        return;
        
    }
    
    //----------------------------------------------------------------------------//
    // DRAW FREQUENCY ENVELOPE
    //----------------------------------------------------------------------------//
    
    void drawFrequencyEnvelope(Envelope tempEnv){
        
        float envPosX = rect->getX();
        float envPosY = rect->getY() + rect->getHeight();
        
        float prevX = envPosX;
        float prevY = envPosY
        + (1 - toOriginal(tempEnv.getValue(0.0f/rect->getWidth()))
           * rect->getHeight());
        float currentX, currentY, nextX, nextY, halfwayBetweenX;
        
        /* Draw Envelope */
        for (int i=0; i < rect->getWidth(); i++) {
            
            currentX = envPosX + i;
            currentY = envPosY
            + (1 - toOriginal(tempEnv.getValue((double)i/rect->getWidth())) * rect->getHeight());
            
            ofCircle(currentX, currentY, 1.0f);
            
            ofxUIDrawLine(prevX, prevY, currentX, currentY);
            
            prevX = currentX;
            prevY = currentY;
            
        }
        
        for (int i=0; i < tempEnv.points.size()-1 && 1 < tempEnv.points.size();
             i++)
        {
            
            currentX = envPosX
            + tempEnv.points.at(i).time *rect->getWidth();
            currentY = rect->getY()
            + (1 - toOriginal(tempEnv.points.at(i).value)) *rect->getHeight();
            
            nextX = envPosX
            + tempEnv.points.at(i+1).time *rect->getWidth();
            nextY = rect->getY()
            + (1 - toOriginal(tempEnv.points.at(i+1).value)) *rect->getHeight();
            
            halfwayBetweenX = (currentX+nextX)/2;
            
            /* Draw Points */
            ofCircle(currentX, currentY, pointNodeRadius);
            
            /* Draw Bezier Curve Control Squares */
            ofxUIDrawRect(halfwayBetweenX
                          - (pointNodeRectWidth/2),
                          envPosY
                          + 1
                          - toOriginal(tempEnv.getValue((halfwayBetweenX-envPosX)/rect->getWidth()))
                          * rect->getHeight()
                          - (pointNodeRectHeight/2),
                          pointNodeRectWidth,
                          pointNodeRectHeight);
            
        }
        
        return;
        
    }
    
    //----------------------------------------------------------------------------//
    // CHECK FOR POINT NODE
    //----------------------------------------------------------------------------//
    /* Will check for point (time == value.x, value == 1-value.y) within circle
     radius */
    
    void checkForPointNode()
    {
        
        Envelope tempEnv = *envelope;
        
        float pX, pY, difference;
        float rW = rect->getWidth();
        float rH = rect->getHeight();
        int size = tempEnv.points.size();
        
        for (int i=0; i<size; i++) {
            
            pX = tempEnv.points.at(i).time;
            pY = tempEnv.points.at(i).value;
            
            difference = abs( (pX*rW + pY*rH) - (value.x*rW + (1-value.y)*rH) );
            
            if (difference <= pointNodeRadius && isRightClick == false) {
                isPointGrabbed = true;
                grabbedPoint = &envelope->points.at(i);
                return;
            }
            else if (difference <= pointNodeRadius && isRightClick == true) {
                envelope->points.erase(envelope->points.begin()+i);
            }
            else {
                isPointGrabbed = false;
            }
            
            /* Check for Curve Nodes */
            if (i < size-1) {
                checkForCurveNode(tempEnv, i);
                if (isCurveGrabbed == true) {
                    return;
                }
            }
            
        }
        
        return;
        
    }
    
    //----------------------------------------------------------------------------//
    // CHECK FOR CURVE NODE
    //----------------------------------------------------------------------------//
    
    void checkForCurveNode(Envelope tempEnv, int i)
    {
        
        float currentX, currentY, nextX, nextY, difference,
            halfwayBetweenX, halfwayBetweenY;
        float rW = rect->getWidth();
        float rH = rect->getHeight();
        
        currentX = tempEnv.points.at(i).time;
        currentY = 1.0f - tempEnv.points.at(i).value;
        nextX = tempEnv.points.at(i+1).time;
        nextY = 1.0f - tempEnv.points.at(i+1).value;
        
        halfwayBetweenX = (currentX+nextX)/2.0f;
        halfwayBetweenY = tempEnv.getValue(halfwayBetweenX);
        
        difference = abs( (halfwayBetweenX*rW + halfwayBetweenY*rH)
                                - (value.x*rW + (1-value.y)*rH) );
        
        if (difference <= pointNodeRadius && isRightClick == false) {
            isCurveGrabbed = true;
            grabbedPoint = &envelope->points.at(i);
            nextPoint = &envelope->points.at(i+1);
            return;
        }
        else {
            isCurveGrabbed = false;
        }
        
        return;
        
    }
    
    //----------------------------------------------------------------------------//
    // MOVE GRABBED POINT
    //----------------------------------------------------------------------------//
    
    void moveGrabbedPoint()
    {
        
        if (isPointGrabbed == true) {
            
            grabbedPoint->time = value.x;
            
            grabbedPoint->value = 1 - value.y;
            cout << "x = " + ofToString(value.x) + " | y = " + ofToString(value.y)
            << endl;
        }
        
        return;
        
    }
    
    //----------------------------------------------------------------------------//
    // MOVE GRABBED POINT
    //----------------------------------------------------------------------------//
    
    void moveGrabbedCurve()
    {
        
        if (isCurveGrabbed == true) {
            
            float curveMover;
            float curveBasePoint = (grabbedPoint->value + nextPoint->value)/2.0f;
            
            if (nextPoint->value >= grabbedPoint->value) {
                curveMover = ofMap((1-value.y),
                                   curveBasePoint, nextPoint->value,
                                   0.0f, 1.0f);
            }
            else if (nextPoint->value < grabbedPoint->value) {
                curveMover = ofMap((1-value.y),
                                   curveBasePoint, grabbedPoint->value,
                                   0.0f, -1.0f);
            }
            
            grabbedPoint->curve = ofClamp(curveMover, -1.0f, 1.0f);
            
        }
        
        return;
        
    }
    
    //----------------------------------------------------------------------------//
    // CONVERT TO FREQUENCY
    //----------------------------------------------------------------------------//
    
    double toFrequency(double value)
    {
        
        value = value-1;
        
        double frequency = pow(value, 3.0);
        
        frequency += 1;
        
        return frequency;
        
    }
    
    //----------------------------------------------------------------------------//
    // CONVERT TO ORIGINAL
    //----------------------------------------------------------------------------//
    
    double toOriginal(double frequency)
    {
        
        double original = pow(frequency, 1.0/3.0);
        
        return original;
        
    }
    
    //----------------------------------------------------------------------------//
    //
    //----------------------------------------------------------------------------//
    
    
    
}; 

#endif
