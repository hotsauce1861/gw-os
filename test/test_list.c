#include "gw_list.h"


void print_list(gw_list* plist){
    while(plist != NULL){
        printf("%d\n",plist->data);
        plist = plist->next;
    }
}

void test_list_insert_last(void){
    gw_list* plist = gw_list_init();
    gw_list_node *pnode1 = gw_list_node_init(111);
    gw_list_node *pnode2 = gw_list_node_init(222);
    gw_list_node *pnode3 = gw_list_node_init(333);
    gw_list_node *pnode4 = gw_list_node_init(444);
    gw_list_node *pnode5 = gw_list_node_init(555);
    gw_list_node *pnode6 = gw_list_node_init(666);
    gw_list_insert_node_last(plist,pnode1);
    gw_list_insert_node_last(plist,pnode2);
    gw_list_insert_node_last(plist,pnode3);
    gw_list_insert_node_last(plist,pnode4);
    gw_list_insert_node_last(plist,pnode5);
    gw_list_insert_node_last(plist,pnode6);
    print_list(plist);
}

void test_list_insert_first(void){
    gw_list* plist = gw_list_init();
    gw_list_node *pnode1 = gw_list_node_init(111);
    gw_list_node *pnode2 = gw_list_node_init(222);
    gw_list_node *pnode3 = gw_list_node_init(333);
    gw_list_node *pnode4 = gw_list_node_init(444);
    gw_list_node *pnode5 = gw_list_node_init(555);
    gw_list_node *pnode6 = gw_list_node_init(666);
    gw_list_insert_node_first(plist,pnode1);
    gw_list_insert_node_first(plist,pnode2);
    gw_list_insert_node_first(plist,pnode3);
    gw_list_insert_node_first(plist,pnode4);
    gw_list_insert_node_first(plist,pnode5);
    gw_list_insert_node_first(plist,pnode6);
    print_list(plist);
}
