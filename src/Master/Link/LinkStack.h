#ifndef LINKSTACK_H
#define LINKSTACK_H
#include "Link.h"
#include <vector>



class LinkStack
{
    std::vector <Link * > links;
public:
    LinkStack();
    void update ();
    void updateFomAud();
    void updateFromMatr();

    int addFromAud (AudioMod* fromAud, int nAudLink, MatrixMod* toMatr, int nMatrLink);
    int addFromMatr (MatrixMod* fromMatr, int nMatrLink,  AudioMod* toAud, int  nAudLink);


};

#endif // LINKSTACK_H
