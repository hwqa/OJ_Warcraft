#include<bits/stdc++.h>
using namespace std;
int N,ap_ar,dloy,DDL;
int hp_i[5],ap_i[5];
enum eweap{sword,bomb,arrow};
enum ewarr{dragon,ninja,iceman,lion,wolf};
char s_out[100];
struct printi{
    char s[100];
    int p,id,c;
    printi(int _p=0,int _id=0,int _c=0):p(_p),id(_id),c(_c){
        strcpy(s,s_out);
    }
    bool operator<(const printi&b)const{
        if(p!=b.p)return p<b.p;if(id!=b.id)return id<b.id;return c<b.c;
    }
};
vector<printi>vecout;









class weapon;
class warrior;
class warrior;
class weapon{
    protected:
    void del();
    public:
    int ap;warrior*sol;
    weapon(warrior*p,eweap id=bomb,int v=0):sol(p),idx(id),ap(v){}
    virtual void att(warrior*x=nullptr){}
    eweap idx;
};
class warrior{
    public:
    static const char*nam[5];
    warrior(ewarr e):weap{nullptr,nullptr,nullptr},idx(e),hp(hp_i[e]),ap(ap_i[e]){}
    void warrior1(int x,int y);
    void outp(const char*s="");
    void outp1(const char*s="");
    weapon*weap[3];
    ewarr idx;
    int hp,ap,hp0,ord,co,ci;
    bool bomb(warrior*A);
    int AP();
    virtual int APb();
    virtual void win(warrior*x);
    virtual void draw();
    virtual void attb(warrior*x);
    virtual void wlk();
    void att(warrior*x);
    void okil();
    void repo();
    virtual void mlife(int _hp);
    ~warrior(){
        delete weap[0];
        delete weap[1];
        delete weap[2];
    }
};
class city{
    protected:
    int lstw,lstf,ord;
    void win(int winner);
    public:
    city(int id,int v=0):lstw(-1),hp(v),R(nullptr),B(nullptr),fl((id+1)%2),lstf(-1),ord(id){}
    int hp,fl,lst;
    warrior*R,*B;
    void bomb();
    void att();
    void rlion();
    ~city(){delete R;delete B;}
};









void weapon::del(){
    assert(sol->weap[idx]==this);sol->weap[idx]=nullptr;delete this;
}
class Sword:public weapon{
    public:
    Sword(warrior*p,int v):weapon(p,sword,v){}
    void att(warrior*p)override{
        p->hp-=ap;
        ap*=0.8;
        if(!ap)del();
    }
};
class Arrow:public weapon{
    public:
    int tim;
    Arrow(warrior*p):weapon(p,arrow,ap_ar),tim(3){}
    void att(warrior*A)override{
        A->hp-=ap;
        sol->outp("shot");
        if(A->hp<=0)strcat(s_out," and killed"),A->outp1();
        vecout.emplace_back(sol->ci,sol->co);
        if(--tim==0)del();
    }
};
class Factory {
    public:
    static weapon* CreateO(int k,warrior*x) {
        int v=x->ap*0.2;
        switch (k) {
            case 0:
                return v?(new Sword(x,v)):nullptr;
            case 1:
                return new weapon(x);
            case 2:
                return new Arrow(x);
        }
    }
};


























const char*warrior::nam[]={"dragon","ninja","iceman","lion","wolf"};
void warrior::warrior1(int x,int y){
    ord=x,co=y,ci=y?N+1:0;outp("born");
}
void warrior::outp(const char*s){
    sprintf(s_out,"%s %s %d %s",co?"blue":"red",nam[idx],ord,s);
}
void warrior::outp1(const char*s){
    sprintf(s_out,"%s %s %s %d %s",s_out,co?"blue":"red",nam[idx],ord,s);
}
bool warrior::bomb(warrior*A){
    if(AP()>=A->hp){
        if(A->weap[1]){
            A->outp("used a bomb and killed");
            outp1();
            return 1;
        }
    }else if(A->APb()>=hp&&weap[1]){
        outp("used a bomb and killed");
        A->outp1();
        return 1;
    }
    return 0;
}
int warrior::AP(){
    return ap+(weap[0]?weap[0]->ap:0);
}
int warrior::APb(){
    return ap/2+(weap[0]?weap[0]->ap:0);
}
void warrior::win(warrior*x){
    if(x->idx==lion)hp+=max(0,x->hp0);
}
void warrior::draw(){
    
}
void warrior::attb(warrior*x){
    x->hp-=ap/2;if(weap[0])weap[0]->att(x);
    outp("fought back against"),x->outp1("in city"),
    sprintf(s_out,"%s %d",s_out,ci);
    vecout.emplace_back(ci,7,co);
}
void warrior::wlk(){
    if(!co){
        if(++ci==N+1){
            outp("reached blue headquarter with");
            sprintf(s_out,"%s %d elements and force %d",s_out,hp,ap);
            vecout.emplace_back(ci,-2);
        }else{
            outp("marched to city");
            sprintf(s_out,"%s %d with %d elements and force %d",s_out,ci,hp,ap);
            vecout.emplace_back(ci,co);
        }
    }else{
        if(--ci==0){
            outp("reached red headquarter with");
            sprintf(s_out,"%s %d elements and force %d",s_out,hp,ap);
            vecout.emplace_back(ci,-2);
        }else{
            outp("marched to city");
            sprintf(s_out,"%s %d with %d elements and force %d",s_out,ci,hp,ap);
            vecout.emplace_back(ci,co);
        }
    }
}
void warrior::att(warrior*x){
    if(weap[0])weap[0]->att(x);
    x->hp-=ap;
    outp("attacked"),x->outp1("in"),
        sprintf(s_out,"%s city %d with %d elements and force %d",s_out,ci,hp,ap);
    vecout.emplace_back(ci,6,co);
    if(x->hp>0)x->attb(this);
    if(hp<=0)okil();else if(x->hp<=0)x->okil();
}
void warrior::okil(){
    outp("was killed in city"),sprintf(s_out,"%s %d",s_out,ci);
    vecout.emplace_back(ci,8,co);
}
void warrior::repo(){
    if(!weap[0]&&!weap[1]&&!weap[2])outp("has no weapon ");else{
        outp("has ");
        if(weap[2])sprintf(s_out,"%sarrow(%d),",s_out,static_cast<Arrow*>(weap[2])->tim);
        if(weap[1])sprintf(s_out,"%sbomb,",s_out);
        if(weap[0])sprintf(s_out,"%ssword(%d),",s_out,weap[0]->ap);
        s_out[(int)strlen(s_out)-1]=0;
    }
    vecout.emplace_back();
}
void warrior::mlife(int v){
}

class Dragon:public warrior{
    private:
    double conf;
    public:
    Dragon():warrior(dragon){}
    void yell(){
        if(conf>=0.8&&hp>0){
            outp("yelled in city"),sprintf(s_out,"%s %d",s_out,ci);
            vecout.emplace_back(ci,9,co);
        }
    }
    void win(warrior*x)override{
        warrior::win(x);
        conf+=0.2;
    }
    void draw()override{
        conf-=0.2;
    }
    void mlife(int _hp)override{
        conf=1.0*_hp/hp;
        sprintf(s_out,"%s\nIts morale is %.2f",s_out,conf);
        weap[ord%3]=Factory::CreateO(ord%3,this);
    }
};
class Ninja:public warrior{
    public:
    Ninja():warrior(ninja){}
    void attb(warrior*x)override{}
    int APb()override{return 0;}
    void mlife(int _hp)override{
        weap[ord%3]=Factory::CreateO(ord%3,this);
        weap[(ord+1)%3]=Factory::CreateO((ord+1)%3,this);
    }

};
class Iceman:public warrior{
    private:
    int T;
    public:
    Iceman():warrior(iceman),T(2){}
    void wlk()override{
        if(--T==0){
            hp=max(hp-9,1);
            ap+=20;
            T=2;
        }
        warrior::wlk();
    }
    void mlife(int _hp)override{
        weap[ord%3]=Factory::CreateO(ord%3,this);
    }
    
};
class Lion:public warrior{
    private:
    int loy;
    public:
    Lion():warrior(lion){}
    void draw()override{
        loy-=dloy;
    }
    void mlife(int _hp)override{
        loy=_hp;
        sprintf(s_out,"%s\nIts loyalty is %d",s_out,loy);
    }
    bool ran(){
        if(loy>0)return 0;
        outp("ran away");
        vecout.emplace_back();
        return 1;
    }
};
class Wolf:public warrior{
    public:
    Wolf():warrior(wolf){}
    void win(warrior*x)override{
        warrior::win(x);
        for(int i=0;i<3;++i)if(!weap[i]&&x->weap[i]){
            swap(weap[i],x->weap[i]);
            weap[i]->sol=this;
        }
    }
};




















void city::win(int winner){
    if(!winner)R->win(B);else B->win(R);
    if(lstw==winner){
        if(winner!=lstf){
            sprintf(s_out,"%s flag raised in city %d",winner?"blue":"red",ord);
            vecout.emplace_back(ord,11);
        }
        fl=lstf=winner;
    }
    lstw=lst=winner;
}
void city::bomb(){
    if(R&&B&&R->hp>0&&B->hp>0){
        bool t=fl?B->bomb(R):R->bomb(B);
        if(t){
            vecout.emplace_back();
            delete R;delete B;
            R=B=nullptr;
        }
    }
}

void city::att(){
    lst=-1;
    if(R)R->hp0=R->hp;
    if(B)B->hp0=B->hp;
    if(R&&B&&R->hp>0&&B->hp>0){
        if(!fl)R->att(B);else B->att(R);
    }
    if(R&&B){
        if(R->idx==dragon&&!fl)static_cast<Dragon*>(R)->yell();
        if(B->idx==dragon&&fl)static_cast<Dragon*>(B)->yell();
        if((R->hp>0)^(B->hp>0)){
            if(R->hp>0)win(0);else win(1);
        }else if(R->hp>0){
            lstw=-1;
            R->draw(),B->draw();
        }
    }
    if(R&&R->hp<=0){
        delete R;R=nullptr;
    }
    if(B&&B->hp<=0){
        delete B;B=nullptr;
    }
}
void city::rlion(){
    if(R&&R->idx==lion&&static_cast<Lion*>(R)->ran()){
        delete R;R=nullptr;
    }
    if(B&&B->idx==lion&&static_cast<Lion*>(B)->ran()){
        delete B;B=nullptr;
    }
}
class headq:public city{
    private:
    int wcnt;warrior*nxt;
    warrior*gnxt(){
        ++wcnt;
        if(!ord){
            switch(nxt->idx){
                case iceman:return new Lion;
                case lion:return new Wolf;
                case wolf:return new Ninja;
                case ninja:return new Dragon;
                case dragon:return new Iceman;
            }
        }else{
            switch(nxt->idx){
                case lion:return new Dragon;
                case dragon:return new Ninja;
                case ninja:return new Iceman;
                case iceman:return new Wolf;
                case wolf:return new Lion;
            }
        }
    }

    public:
    headq(int id,int v):city(id,v),wcnt(1){//,nxt(id?(new Lion):(new Iceman)){
        if(id)nxt=new Lion;else nxt=new Iceman;
    }
    void mlife(){
        if(hp<nxt->hp)return;
        hp-=nxt->hp;
        nxt->warrior1(wcnt,ord!=0);
        nxt->mlife(hp);
        vecout.emplace_back();
        (ord?B:R)=nxt;
        nxt=gnxt();
    }
};


















class All{
    public:
    int hour;
    city*a[22];
    void init(){
        int hp0;cin>>hp0>>N>>ap_ar>>dloy>>DDL;
        for(int i=0;i<5;++i)cin>>hp_i[i];
        for(int i=0;i<5;++i)cin>>ap_i[i];
        for(int i=1;i<=N;++i)a[i]=new city(i);
        a[0]=new headq(0,hp0),a[N+1]=new headq(N+1,hp0);
        hour=0;
    }
    void solve(){
        init();
        city*S=a[0],*T=a[N+1];
        for(;;++hour){
            static_cast<headq*>(S)->mlife(),static_cast<headq*>(T)->mlife();
            if(!outp(0,0))return;
            for(int i=0;i<=N+1;++i)a[i]->rlion();
            if(!outp(5,0))return;
            for(int i=N;~i;--i)if(a[i]->R){
                a[i]->R->wlk();
                if(i==N&&a[i+1]->R){
                    strcpy(s_out,"blue headquarter was taken");
                    vecout.emplace_back(N+1,-1);
                    delete a[i+1]->R;
                }
                a[i+1]->R=a[i]->R,a[i]->R=nullptr;
            }
            for(int i=1;i<=N+1;++i)if(a[i]->B){
                a[i]->B->wlk();
                if(i==1&&a[i-1]->B){
                    strcpy(s_out,"red headquarter was taken");
                    vecout.emplace_back(0,-1);
                    delete a[i-1]->B;
                }
                a[i-1]->B=a[i]->B,a[i]->B=nullptr;
            }
            if(!outp(10))return;
            for(int i=1;i<=N;++i)a[i]->hp+=10;
            for(int i=1;i<=N;++i){
                if(a[i]->R&&!a[i]->B){
                    a[i]->R->outp("earned");
                    sprintf(s_out,"%s %d elements for his headquarter",s_out,a[i]->hp);
                    vecout.emplace_back();
                    S->hp+=a[i]->hp,a[i]->hp=0;
                }
                if(a[i]->B&&!a[i]->R){
                    a[i]->B->outp("earned");
                    sprintf(s_out,"%s %d elements for his headquarter",s_out,a[i]->hp);
                    vecout.emplace_back();
                    T->hp+=a[i]->hp,a[i]->hp=0;
                }
            }
            if(!outp(30,0))return;
            for(int i=N;i;--i)if(a[i-1]->R&&a[i]->B&&a[i-1]->R->weap[2]){
                a[i-1]->R->weap[2]->att(a[i]->B);
            }
            for(int i=1;i<=N;++i)if(a[i+1]->B&&a[i]->R&&a[i+1]->B->weap[2]){
                a[i+1]->B->weap[2]->att(a[i]->R);
            }
            if(!outp(35))return;
            for(int i=1;i<=N;++i)a[i]->bomb();
            if(!outp(38,0))return;
            for(int i=1;i<=N;++i)a[i]->att();
            for(int i=1;i<=N;++i)if(a[i]->lst==0){
                int v=min(S->hp,8);S->hp-=v,a[i]->R->hp+=v;
            }
            for(int i=N;i;--i)if(a[i]->lst==1){
                int v=min(T->hp,8);T->hp-=v,a[i]->B->hp+=v;
            }
            for(int i=1;i<=N;++i)if(~a[i]->lst&&a[i]->hp){
                if(!a[i]->lst){
                    a[i]->R->outp();S->hp+=a[i]->hp;
                    sprintf(s_out,"%searned %d elements for his headquarter",s_out,a[i]->hp);
                }else{
                    a[i]->B->outp();T->hp+=a[i]->hp;
                    sprintf(s_out,"%searned %d elements for his headquarter",s_out,a[i]->hp);
                }
                vecout.emplace_back(i,10);
                a[i]->hp=0;
            }
            if(!outp(40))return;
            sprintf(s_out,"%d elements in red headquarter",S->hp);
            vecout.emplace_back();
            sprintf(s_out,"%d elements in blue headquarter",T->hp);
            vecout.emplace_back();
            if(!outp(50,0))return;
            for(int i=0;i<=N+1;++i)if(a[i]->R)a[i]->R->repo();
            for(int i=0;i<=N+1;++i)if(a[i]->B)a[i]->B->repo();
            if(!outp(55,0))return;
        }
    }
    void clear(){
        vecout.clear();
        for(int i=0;i<=N+1;++i)delete a[i];
    }
    bool outp(int t,bool s=1){
        if(hour*60+t>DDL)return 0;
        if(s)sort(vecout.begin(),vecout.end());
        for(auto k:vecout)printf("%03d:%02d %s\n",hour,t,k.s);
        for(auto k:vecout)if(k.id==-1)return 0;
        vecout.clear();
        return 1;
    }
}_All;
int main(){
    int cases;
    cin>>cases;
    for(int i=1;i<=cases;++i){
        printf("Case %d:\n",i);
        _All.solve(),_All.clear();
        cerr<<i<<endl;
    }
    return 0;
}

