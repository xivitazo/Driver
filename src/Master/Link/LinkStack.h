#ifndef _LINKSTACK_H
#define _LINKSTACK_H


class Link;
class AudioMod;
class MatrixMod;

class LinkStack {
  private:
    std::vector<Link*> links;


  public:
    LinkStack();

    void update();

    void updateFomAud();

    void updateFromMatr();

    int addFromAud(AudioMod * fromAud, int nAudLink, MatrixMod * toMatr, int nMatrLink);

    int addFromMatr(MatrixMod * fromMatr, int nMatrLink, AudioMod * toAud, int nAudLink);

};
#endif
