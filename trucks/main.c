#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef struct{
    int weight;
    int currtruck;
    int besttruck;
}pack_t;
//each pack is loaded in which truck

pack_t *load(char *,int *);
int place_r(pack_t *, int, int *,int,int,int);
void display(pack_t *,int, int);
int main(int argc,char *argv[])
{
    int packnum,neededTruck;
    int *trucks;
    pack_t *packs;

    if(argc!=2){
        printf("error in C.L parameter!\n");
        exit(0);
    }
    packs=load(argv[1],&packnum);
    trucks=(int *)calloc(packnum,sizeof(int));
    neededTruck=place_r(packs,packnum,trucks,0,packnum+1,0);
    display(packs,packnum,neededTruck);
    free(packs);
    free(trucks);
    printf("%d",neededTruck);
    return 0;
}

pack_t *load(char *fn,int *num){
    int n,i;
    FILE *fp;
    pack_t *packs;
    fp=fopen(fn,"r");
    if(fp==NULL){
        printf("error in opening file!\n");
        exit(0);
    }
    fscanf(fp,"%d",&n);
    packs=(pack_t *)malloc(n*sizeof(pack_t));
    if(fp==NULL){
        printf("error in allocation!\n");
        exit(0);
    }
    for(i=0;i<n;i++){
        fscanf(fp,"%d",&packs[i].weight);
        packs[i].besttruck=packs[i].currtruck=-1;
    }
    *num=n;
    return packs;
}
//ntcurr is the number of trucks currently=0
//ntbest is the minimum number of trucks needed=10+1
int place_r(pack_t *packs,int packnum, int *trucks,int ntcurr,int ntbest,int level){
    int i;
    if(level==packnum){
        if(ntcurr<ntbest){
            for(i=0;i<packnum;i++){
                packs[i].besttruck=packs[i].currtruck;
            }
            return ntcurr;
        }
        return ntbest;
    }

    for(i=0;i<ntcurr;i++){
        if(trucks[i]+packs[level].weight<=MAX){
            packs[level].currtruck=i;
            trucks[i]+=packs[level].weight;
            ntbest=place_r(packs,packnum,trucks,ntcurr,ntbest,level+1);
            packs[level].currtruck=-1;
            trucks[i]-=packs[level].weight;
        }
    }
    if(ntcurr<ntbest){
        packs[level].currtruck=i;
        trucks[i]+=packs[level].weight;
        ntbest=place_r(packs,packnum,trucks,ntcurr+1,ntbest,level+1);
        packs[level].currtruck=-1;
        trucks[i]-=packs[level].weight;
    }

    return ntbest;
}
void display(pack_t *packs,int packnum,int neededTruck){
    int i,j,weight;
    printf("%d trucks are needed.\n",neededTruck);
    for(i=0;i<neededTruck;i++){
        weight=0;
        for(j=0;j<packnum;j++){
            if(packs[j].besttruck==i){
                weight+=packs[j].weight;
            }
        }
        printf("#Truck %d , Weight %d\n",i,weight);
        for(j=0;j<packnum;j++){
            if(packs[j].besttruck==i){
                printf("package %d, weight %d\n",j,packs[j].weight);
            }
        }

    }

    return;
}
