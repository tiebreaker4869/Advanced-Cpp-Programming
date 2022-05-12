
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

class Color {
    private:
        int r;
        int g;
        int b;
    public:
        Color():r(0),g(0),b(0){}

        Color(const Color& c){
            this->r = c.get_r();
            this->g = c.get_g();
            this->b = c.get_b();
        }
        
        int get_r() const{return r;}
        int get_g() const{return g;}
        int get_b() const{return b;}

        void set_color(int r, int g, int b){
            this->r = r;
            this->g = g;
            this->b = b;
        }

        void set_color(Color& c){
            this->r = c.get_r();
            this->g = c.get_g();
            this->b = c.get_b();
        }
};

class Rectangle {
    protected:
        Color color;
    public:
        std::string polyid;
        Rectangle(std::string id):color(Color()),polyid(id){}
        virtual void set_color(Color c)=0;
        int get_r()const {return color.get_r();}
        int get_g()const {return color.get_g();}
        int get_b()const {return color.get_b();}
        std::string get_id() const{return polyid;}
};

class Normal : public Rectangle {
    public:
        Normal(std::string id):Rectangle(id){}
        void set_color(Color c) override {
            color.set_color(c);
        }
};

class Reverse : public Rectangle {
    public:
        Reverse(std::string id):Rectangle(id){}
        void set_color(Color c) override {
            color.set_color(255-c.get_r(), 255-c.get_g(), 255-c.get_b());
        }
};

class Single : public Rectangle {
    public:
        Single(std::string id):Rectangle(id){}
        void set_color(Color c) override {
            color.set_color(c.get_r(), 0, 0);
        }
};

class RectangleFactory {
    public:
        static Rectangle* createRectangle(std::string type, std::string id);
};

Rectangle* RectangleFactory::createRectangle(std::string type, std::string id){
            if(type == "normal")
                return new Normal(id);
            if(type == "single")
                return new Single(id);
            if(type == "reverse")
                return new Reverse(id);
        
        std::cout << "invalid type" << std::endl;
        
        return nullptr;
}

void print(const std::vector<Rectangle*>& recs){
    for(int i = 0; i < recs.size(); i ++){
        std::cout << recs[i]->get_id() << " " << recs[i]->get_r() << " " << recs[i]->get_g() << " "
        << recs[i]->get_b() << std::endl;
    }
}

inline int calculate_gray_val(const int r,const int g, const int b){
    return r * 0.299 + g * 0.587 + b * 0.114;
}

bool cmp_by_id(const Rectangle* rec1, const Rectangle* rec2){
    return rec1->get_id() < rec2->get_id();
}

bool cmp_by_gray(const Rectangle* rec1, const Rectangle* rec2){
    return calculate_gray_val(rec1->get_r(), rec1->get_g(), rec1->get_b()) < 
        calculate_gray_val(rec2->get_r(), rec2->get_g(), rec2->get_b());   
}

int main(){
    std::unordered_map<std::string, std::vector<Rectangle*>> group_record;
    int cmd_num;
    std::vector<Rectangle*> recs;
    std::cin >> cmd_num;
    while(cmd_num --){
        std::string cmd;
        std::cin >> cmd;
        if(cmd == "Add"){
            std::string polyid, type;
            std::cin >>type >> polyid;
            Rectangle* rec = RectangleFactory::createRectangle(type, polyid);
            recs.push_back(rec);
        }else if(cmd == "Group"){
            int n;
            std::vector<std::string> indices; 
            std::cin >> n;
            indices.resize(n);
            for(int i = 0; i < n; i ++){
                std::cin >> indices[i];
            }
            std::string groupId;
            std::cin >> groupId;
            if(group_record.count(groupId) == 0)group_record[groupId] = std::vector<Rectangle*>();
            for(int i = 0; i < recs.size(); i ++){
                for(int j = 0; j < indices.size(); j ++){
                    if(indices[j] == recs[i]->get_id()){
                        group_record[groupId].push_back(recs[i]);
                        break;
                    }
                }
            }
        }else if(cmd == "Set"){
            std::string polyid;
            int r, g, b; 
            std::cin >> polyid >> r >> g >> b; 
            Color c; 
            c.set_color(r, g, b);
            if(polyid[0] == 'P') {
                for (int i = 0; i < recs.size(); i++) {
                    if (recs[i]->get_id() == polyid) {
                        recs[i]->set_color(c);
                        break;
                    }
                }
            }else {
                const std::vector<Rectangle*>& group = group_record[polyid];
                for(int i = 0; i < group.size(); i ++){
                    group[i]->set_color(c);
                }
            }
        }else {
            std::cout << "invalid command !" << std::endl;
        }
    }
    std::string output;
    std::cin >> output;
    if(output == "Normal"){
        std::sort(recs.begin(), recs.end(), cmp_by_id);
        print(recs);
    }else if(output == "Gray"){
        std::sort(recs.begin(), recs.end(), cmp_by_gray);
        print(recs);
    }

    return 0;
}