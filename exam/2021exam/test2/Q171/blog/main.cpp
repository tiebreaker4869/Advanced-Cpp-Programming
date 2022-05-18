#include <iostream>
#include <vector>

enum Type {
    SELF, BIFANS, FANS
};

class Blog {
private:
    int userId;
    Type type;
    int blogId;
public:
    int get_userId(){return userId;}
    int get_blogId(){return blogId;}
    Type get_type(){return type;}
    Blog(int uid, Type t, int bid);
};

//TODO: constructor with args

std::vector<Blog> blogs;
std::vector<std::vector<bool>> followRelationship;
std::vector<int> follow;
std::vector<int> fans;

Blog::Blog(int uid, Type t, int bid):userId(uid),type(t),blogId(bid){

}

void init(){
    const int maxn = 1000;
    followRelationship.resize(maxn);
    for(int i = 0; i < followRelationship.size(); i ++){
        followRelationship[i].resize(maxn);
        for(int j = 0; j < followRelationship[i].size(); j ++){
            if(i != j)followRelationship[i][j] = false;
            else followRelationship[i][j] = true;
        }
    }

    follow.resize(maxn);
    fans.resize(maxn);
    for(int i = 0; i < follow.size(); i ++){
        follow[i] = 0;
        fans[i] = 0;
    }
}

void addFollow(int followerId, int followeeId){
    followRelationship[followerId][followeeId] = true;
    follow[followerId] ++;
    fans[followeeId] ++;
}

void unFollow(int followerId, int followeeId){
    followRelationship[followerId][followeeId] = false;
    follow[followerId] --;
    fans[followeeId] --;
}

int getFollows(int userId){
    return follow[userId];
}

int getFans(int userId){
    return fans[userId];
}

int getBlogs(int userId){
    int cnt = 0;
    for(int i = 0; i < blogs.size(); i ++){
        if(blogs[i].get_userId() == userId)cnt ++;
    }

    return cnt;
}

std::vector<int> getRecent(int userId, int num, Type type){
    std::vector<int> blogIds;
    if(type == SELF){
        //查看自己发的，仅自己可见的微博
        for(int i = blogs.size()-1; i >= 0; i --){
            if(userId == blogs[i].get_userId()){
                blogIds.push_back(blogs[i].get_blogId());
                if(blogIds.size() == num)break;
            }
        }
    }else if(type == BIFANS){
        //查看好友圈的微博(包括自己的)
        for(int i = blogs.size()-1; i >= 0; i --){
            if((blogs[i].get_userId() == userId) || (blogs[i].get_type() != SELF && followRelationship[userId][blogs[i].get_userId()] && followRelationship[blogs[i].get_userId()][userId])){
                blogIds.push_back(blogs[i].get_blogId());
                if(blogIds.size() == num){
                    break;
                }
            }
        }
    }else {
        //查看关注的人的微博(包括自己)
        for(int i = blogs.size()-1; i >= 0; i --){
            if(blogs[i].get_userId() == userId || (blogs[i].get_type() == FANS && followRelationship[userId][blogs[i].get_userId()])){
                blogIds.push_back(blogs[i].get_blogId());
                if(blogIds.size() == num)break;
            }
        }
    }

    return blogIds;
}

int main(){
    init();
    int n;
    std::cin >> n;
    std::string cmd;
    while(n -- ){
        std::cin >> cmd;
        if(cmd == "post"){
            int userId, weiboId, t;
            Type type;
            std::cin >> userId >> weiboId >> t;
            type = (Type)t;
            Blog blog(userId, type, weiboId);
            blogs.push_back(blog);
        }else if(cmd == "follow"){
            int followerId, followeeId;
            std::cin >> followerId >> followeeId;
            addFollow(followerId, followeeId);
        }else if(cmd == "unfollow"){
            int followerId, followeeId;
            std::cin >> followerId >> followeeId;
            unFollow(followerId, followeeId);
        }else if(cmd == "getFollows"){
            int userId;
            std::cin >> userId;
            int f = getFollows(userId);
            std::cout << f << std::endl;
        }else if(cmd == "getFans"){
            int userId;
            std::cin >> userId;
            int f = getFans(userId);
            std::cout << f << std::endl;
        }else if(cmd == "getWeibos"){
            int userId;
            std::cin >> userId;
            int w = getBlogs(userId);
            std::cout << w << std::endl;
        }else if(cmd == "getRecent"){
            int userId, num, t;
            Type type;
            std::cin >> userId >> num >> t;
            type = (Type)t;
            std::vector<int> bids = getRecent(userId, num, type);
            for(int i = 0; i < bids.size(); i ++){
                std::cout << bids[i];
                if(i != bids.size() - 1)std::cout << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}
