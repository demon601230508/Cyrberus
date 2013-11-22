//
//  FocalPoint.cpp
//  GenMax
//
//  Created by Mitchell Nordine on 4/11/2013.
//
//

#include "FocalPoint.h"

//--------------------------------------------------------------------------------//
// SETUP FOCALPOINT
//--------------------------------------------------------------------------------//

void FocalPoint::setup(GUI *_gui)
{
    
    gui = _gui;
    guiGlobal = &gui->guiGlobal;
    
    return;
    
}

void FocalPoint::setup(GUI *_gui, float _position)
{
    
    gui = _gui;
    guiGlobal = &gui->guiGlobal;
    
    positions.clear();
    addPosition(_position);
    
    return;
    
}

void FocalPoint::setup(GUI *_gui, vector<float> _positions)
{
    
    gui = _gui;
    guiGlobal = &gui->guiGlobal;
    
    positions.clear();
    addPositions(_positions);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// INITIALISE FOCAL POINT
//--------------------------------------------------------------------------------//

void FocalPoint::initialise()
{
    
    positions.clear();
    
    return;
    
}

//--------------------------------------------------------------------------------//
// SET POSITION
//--------------------------------------------------------------------------------//

float FocalPoint::setPosition(float _position)
{
    
    positions.clear();
    positions.push_back(_position);
    
    return _position;
    
}

//--------------------------------------------------------------------------------//
// ADD POSITION
//--------------------------------------------------------------------------------//

float FocalPoint::addPosition(float _position)
{
    
    positions.push_back(_position);
    sort(positions.begin(), positions.end());
    
    return _position;
    
}

//--------------------------------------------------------------------------------//
// ADD POSITIONS
//--------------------------------------------------------------------------------//

vector<float> FocalPoint::addPositions(vector<float> _positions)
{
    
    for (int i=0; i<_positions.size(); i++) {
        positions.push_back(_positions.at(i));
    }
    sort(positions.begin(), positions.end());
    
    return positions;
    
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//