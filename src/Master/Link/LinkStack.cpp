
#include "LinkStack.h"
#include "Link.h"
#include "AudioMod.h"
#include "MatrixMod.h"

LinkStack::LinkStack() {


}

void LinkStack::update() {

    for(int n=0; n<links.size();n++)
    {
        links[n]->update();
    }
}

void LinkStack::updateFomAud() {

    for(int n=0; n<links.size();n++)
    {
        if(links[n]->fromAud)
        {
            links[n]->update();
        }
    }
}

void LinkStack::updateFromMatr() {

    for(int n=0; n<links.size();n++)
    {
        if(!links[n]->fromAud)
        {
            links[n]->update();
        }
    }
}

int LinkStack::addFromAud() {

    links.push_back(new Link (fromAud, nAudLink, toMatr,nMatrLink, true));
    return true;
}

int LinkStack::addFromMatr() {

    links.push_back((new Link (toAud,nAudLink,fromMatr,nMatrLink,false)));
    return true;
}

