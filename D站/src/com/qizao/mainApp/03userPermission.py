from enum import Enum
class state(Enum):
    UNDEFINED = 0
    NORMAL = 1
    VIP = 2
class user:
    def __init__(self ):
        self.state = state.UNDEFINED
    def watch(self):
        print("看1080P视频ing")
class normalUser(user):
    def __init__(self ):
        self.state = state.NORMAL


class vipUser(user):
    def __init__(self ):
        self.state = state.NORMAL
    def watch(self):
        print("看1080K视频ing")
user1 = normalUser( )
user2 = vipUser( )
users = [user1, user2]
for user in users:
    user.watch()