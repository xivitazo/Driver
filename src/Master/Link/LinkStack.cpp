#include "LinkStack.h"

LinkStack::LinkStack()
{

}

void LinkStack::update ()
{
    for(int n=0; n<links.size();n++)
    {
        links[n]->update();
    }
}

void LinkStack::updateFomAud()
{
    for(int n=0; n<links.size();n++)
    {
        if(links[n]->fromAud)
        {
            links[n]->update();
        }
    }
}

void LinkStack::updateFromMatr()
{
    for(int n=0; n<links.size();n++)
    {
        if(!links[n]->fromAud)
        {
            links[n]->update();
        }
    }
}

int LinkStack::addFromAud (AudioMod* fromAud, int nAudLink, MatrixMod* toMatr, int nMatrLink)
{
    links.push_back(new Link (fromAud, nAudLink, toMatr,nMatrLink, true));
    return true;
}

int LinkStack::addFromMatr (MatrixMod* fromMatr, int nMatrLink,  AudioMod* toAud, int  nAudLink)
{
    links.push_back((new Link (toAud,nAudLink,fromMatr,nMatrLink,false)));
    return true;
}
