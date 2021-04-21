from threading import Lock

class BaseMod :
    def __init__ (self, ninlinks : int, noutlinks : int) :
        self.ninlinks = ninlinks
        self.noutlinks = noutlinks
        self.mtx=Lock()

    def getLink (self, nlink : int) :
        if nlink <= self.noutlinks:
            return -1
        self.mtx.acquire()
        value=self.linkOut(nlink)
        self.mtx.release()
        return value
    def setLink (self, nlink : int, value) :
        if nlink <= self.ninlinks :
            return -1
        self.mtx.acquire()
        self.linkIn(nlink, value)
        self.mtx.release
        return True

    def linkIn (self,nlink :int, value):
        pass    
    def linkOut (self, nlink:int):
        return -1

    
  #  def updateLink (nlink : int , val)
  #  def getNInLinks ()
  #  def getLink(nlink : int)
  #  def getNoutLinks ()
  #  def isLinkReady (nlink : int)