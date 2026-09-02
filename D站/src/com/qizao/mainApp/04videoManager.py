class Video():
    def __init__(self,title,author,views,likes,):
        self.title = title
        self.author = author
        self.views = views
        self.likes = likes
    def showInfo(self):
        print("视频标题",self.title)
        print("UP主",self.author)
        print("视频播放量",self.views)
        print("点赞数",self.likes)
    def watch(self):
        self.views += 1
    def likeIt(self):
        self.likes += 1
        print("点赞成功")
        print("当前点赞数：",self.likes)
pythonFromBeginner = Video("Python后端开发入门" ,"D站技术UP主",10000,500)
pythonFromBeginner.showInfo()
pythonFromBeginner.likeIt()