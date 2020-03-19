#ifndef grafo_h
#define grafo_h

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>



#include <queue>



using namespace std;

#define INFOSOC 116726
#define APC 113476
#define C1 113468
#define ISC 113034

#define LCL 129020
#define CL 129011
#define ED 116319
#define FTC 113450
#define IAL 113093
#define C2 113042

#define TP1 117889
#define OAC 116394
#define PE 115045
#define CN 113417
#define A1 113107

#define TAG 117901
#define TP2 117897
#define LC1 117366
#define RDS 116572

#define PC 117935
#define IIA 116653
#define ENGSOF 116441
#define BD 116378
#define LP 116343

#define SO 117960
#define CE 117943
#define AUT 116882
#define SB 116432
#define SI 116416

#define COMP 117951
#define SEC 117927
#define PAA 117536


tuple<int,int,string> infosoc(INFOSOC,2,"INFOSOC");
tuple<int,int,string> apc(APC,6,"APC");
tuple<int,int,string> c1(C1,6,"C1"); 
tuple<int,int,string> isc(ISC,4,"ISC") ;

tuple<int,int,string> lcl(LCL,2,"LCL");
tuple<int,int,string> cl(CL,4,"CL") ;
tuple<int,int,string> ed(ED,4,"ED") ;
tuple<int,int,string> ftc(FTC,4,"FTC") ;
tuple<int,int,string> ial(IAL,4,"IAL") ;
tuple<int,int,string> c2(C2,6,"C2") ;

tuple<int,int,string> tp1(TP1,4,"TP1");
tuple<int,int,string> oac(OAC,4,"OAC") ;
tuple<int,int,string> pe(PE,4,"PE") ;
tuple<int,int,string> cn(CN,4,"CN");
tuple<int,int,string> a1(A1,4,"A1") ;

tuple<int,int,string> tag(TAG,4,"TAG") ;
tuple<int,int,string> tp2(TP2,4,"TP2") ;
tuple<int,int,string> lc1(LC1,4,"LC1") ;
tuple<int,int,string> rds(RDS,4,"RDS") ;

tuple<int,int,string> pc(PC,4,"PCC") ;
tuple<int,int,string> iia(IIA,4,"IIA") ;
tuple<int,int,string> engsof(ENGSOF,4,"ENGSOF") ;
tuple<int,int,string> bd(BD,4,"BD") ;
tuple<int,int,string> lp(LP,4,"LP") ;

tuple<int,int,string> so(SO,4,"SO") ;
tuple<int,int,string> ce(CE,4,"CE");
tuple<int,int,string> aut(AUT,6,"AUT") ;
tuple<int,int,string> sb(SB,4,"SB") ;
tuple<int,int,string> si(SI,4,"SI") ;

tuple<int,int,string> comp(COMP,4,"COMP") ;
tuple<int,int,string> sec(SEC,4,"SEC") ;
tuple<int,int,string> paa(PAA,4,"PAA") ;


// ordem das disciplinas utilizda no txt
tuple<int,int,string> disciplinas[32] = {
        infosoc, apc, c1, isc,
        lcl, cl, ed, ftc, ial, c2,
        tp1, oac, pe, cn, a1, 
        tag, tp2, lc1, rds, 
        pc, iia, engsof, bd, lp,
        so, ce, aut, sb, si,
        comp, sec, paa,
};

// nó da lista de adjacência 
typedef struct node{


    tuple<int,int,string> disciplina;
    int grau;
    vector<struct node*> adj;


}t_node;










#endif