# include <string.h>
# include "sorting.h"

void main(){
    card table[MAX], key;
    int nitem = 0, pos;
    int t, c;

    do{
        printf("input command (1:search / 2:insert / 3:delete / 4. f_search / 5. quit) : ");
        scanf("%d", &c);

        switch(c){
            case 1:
                printf("input no: ");
                scanf("%d", &(key.no));

                t = lv_search(&key, table, &nitem, sizeof(card), cardcmp);
                if(t>-1){
                    printf("searched id: %d / searched name: %s\n", (table[t]).no, (table[t]).name);
                }
                break;

            case 2:
                printf("input no: ");
                scanf("%d", &(key.no));
                printf("input name: ");
                scanf("%s", key.name);

                t = lv_insert(&key, table, &nitem, sizeof(card), cardcmp);
                if(t>-1){
                    printf("insert id: %d / insert name: %s\n", (table[t]).no, (table[t]).name);
                }
                break;

            case 3:
                printf("input no: ");
                scanf("%d", &(key.no));

                t = lv_delete(&key, table, &nitem, sizeof(card), cardcmp);
                if(t>-1){
                    printf("delete id: %d / delete name: %s\n", key.no, key.name);
                }
                break;

            case 4:
                printf("input no: ");
                scanf("%d", &(key.no));

                t = lfv_search(&key, table, &nitem, sizeof(card), cardcmp);
                if(t>-1){
                    printf("searched index: %d\n", t);
                    printf("front id: %d / front name: %s\n", (table[0]).no, (table[0]).name);
                }
                break;
        }
    } while(c<5);
}

int cardcmp(const void *a, const void *b){
    return (((card*)a)->no - ((card*)b)->no);
}
int lv_search(void *key, void *base, int *nelem, int width, FCMP fcmp){
    int i = 0;
    while(fcmp(BASE(i), key) != 0 && i < *nelem) i++;

    return (i < *nelem ? i : -1);
}

int lv_insert(void *key, void *base, int *nelem, int width, FCMP fcmp){
    memcpy(BASE((*nelem)++), key, width);

    return (*nelem)-1;
}

int lv_delete(void *key, void *base, int *nelem, int width, FCMP fcmp){
    int p,i;
    if((*nelem) > 0){
        if((p = lv_search(key, base, nelem, width, fcmp)) < 0) return -1;
        for(i=p+1; i<*nelem; i++) memcpy(BASE(i-1), BASE(i), width);
        (*nelem)--;
        return p;
    }
    return -1;
}

int lfv_search(void *key, void *base, int *nelem, int width, FCMP fcmp){
    int i=0, j;
    void *v;
    while(fcmp(BASE(i), key) != 0 && i < *nelem) i++;
    //if no key return -1
    if(i >= *nelem) return -1;
    v = malloc(width);
    //cpy key
    memcpy(v, BASE(i), width);
    for(j=i-1; j>=0; j--) memcpy(BASE(j+1), BASE(j), width);
    memcpy(BASE(0), v, width);

    return 0;
}
