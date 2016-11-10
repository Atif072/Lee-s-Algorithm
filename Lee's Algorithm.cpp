#include<bits/stdc++.h>

using namespace std;

char Lboard[100][100],Sboard[100][100];
int n,nblocks,bx,by,ntarget,sx,sy,desx,desy;
bool Lblock[10000],Sblock[10000];
int Lpath[10000], dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
int srcX[100],srcY[100],desX[100],desY[100];

bool LeeAlgo(int x1,int y1,int x2,int y2) {
    bool visit[n*n];
    memset(visit,false,(n*n)+1);

    int src=x1*n+y1,des=x2*n+y2;
    queue<int>q;
    q.push(src);
    Lpath[src]=-1;

    while(!q.empty()) {
        int p=q.front();
        visit[p]=true;
        int x=p/n,y=p%n;

        for(int i=0;i<4;i++) {
            int tx=x+dx[i],ty=y+dy[i];
            int id=tx*n+ty;

            if((tx>=0 && tx<n && ty>=0 && ty<n)&&(visit[id]==false)&&(Lblock[id]==false)) {
                if(id==des) {
                     Lpath[id]=p;
                     return true;
                }
                q.push(id);
                Lpath[id]=p;
            }
        }
        q.pop();
    }
    return false;
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    in>>n;
    in>>nblocks;

    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            Lboard[i][j]='0';
            Sboard[i][j]='0';
        }
    }
    memset(Lblock,false,(n*n)+1);
    memset(Sblock,false,(n*n)+1);

    for(int i=0;i<nblocks;i++) {
        in>>bx>>by;
        Lboard[bx][by]='#';
        Sboard[bx][by]='#';
        Lblock[bx*n+by]=true;
        Sblock[bx*n+by]=true;
    }
    bool ans[2][100];

    in>>ntarget;

    for(int i=0;i<ntarget;i++) {
        in>>sx>>sy>>desx>>desy;
        srcX[i]=sx;
        srcY[i]=sy;
        desX[i]=desx;
        desY[i]=desy;
        Lboard[sx][sy]='S';
        Lboard[desx][desy]='T';
    }
    for(int i=0;i<ntarget;i++) {
        sx=srcX[i];
        sy=srcY[i];
        desx=desX[i];
        desy=desY[i];
        //for Lee's algorithm
        if(LeeAlgo(sx,sy,desx,desy)==true) {    //find destination and return Lpath;
            int id=desx*n+desy;
            Lblock[id]=true;
            Lblock[sx*n+sy]=true;

            while(Lpath[id]!=-1) {
                Lboard[Lpath[id]/n][Lpath[id]%n]='*';
                Lblock[Lpath[id]]=true;
                id=Lpath[id];
            }
            Lboard[sx][sy]='S';
            ans[0][i]=true;
        }
        else {      //there is no route
            Lboard[sx][sy]='s';
            Lboard[desx][desy]='t';
            ans[0][i]=false;
           // cout<<endl;
           // cout<<"Net ("<<sx<<","<<sy<<")->("<<desx<<","<<desy<<") cannot be routed."<<endl;
        }
    }

    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) out<<Lboard[i][j]<<" ";
        out<<endl;
    }
    out<<endl;
    for(int i=0;i<ntarget;i++) {
        if(ans[0][i]==false) {
            out<<"Net ("<<sx<<","<<sy<<")->("<<desx<<","<<desy<<") cannot be routed."<<endl;
        }
    }
    return 0;
}


