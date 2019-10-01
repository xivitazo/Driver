#include "Link.h"


Link::Link(AudioMod *link, int nlink):
    link_mod(link),
    link(nlink)
{

}

void Link::update(float &val)
{
    link_mod->update_link(link, val);
}
