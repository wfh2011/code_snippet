#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

#define MAX_ELE_NUMS    (5)

struct Stu {
    unsigned int ulId;
    struct list_head stNode;
};

struct StuList {
    struct list_head stLi;
};

// 打印单个Node信息
static void DL_PrintNode(char *pcPrefix, struct Stu *pstStu) {
    assert((NULL != pcPrefix) && (NULL != pstStu));
    printf("%s, id: %u, addr: %p, node: %p\n", pcPrefix, pstStu->ulId, pstStu, &(pstStu->stNode));
}

// 释放链表的所有数据
void DL_ClearStuLi(struct list_head *pstHead) {
    assert(NULL != pstHead);
    struct Stu *pstStu = NULL;
    struct Stu *pstNextStu = NULL;
    list_for_each_entry_safe(pstStu, pstNextStu, pstHead, stNode) {
        list_del(&(pstStu->stNode));
        DL_PrintNode("free", pstStu);
        free((void *) pstStu);
    }
}

// 打印链表数据
void DL_PrintStuLi(struct list_head *pstHead, int lReverse) {
    assert(NULL != pstHead);
    struct Stu *pstStu = NULL;
    struct Stu *pstNextStu = NULL;
    if (lReverse) {
        list_for_each_entry_safe_reverse(pstStu, pstNextStu, pstHead, stNode) {
            DL_PrintNode("show backward", pstStu);
        }
    } else {
        list_for_each_entry_safe(pstStu, pstNextStu, pstHead, stNode) {
            DL_PrintNode("show forward", pstStu);
        }
    }
}

// 批量添加至链表中
void DL_BatchAddStuLiNodes(struct list_head *pstHead, struct Stu **ppstStus, unsigned int ulNodeNum, int lAddTail) {
    assert((NULL != pstHead) && (NULL != ppstStus));
    struct Stu *pstStu = NULL;
    if (lAddTail) {
        for (unsigned int i = 0; i < ulNodeNum; ++i) {
            pstStu = ppstStus[i];
            list_add_tail(&(pstStu->stNode), pstHead);
        }
    } else {
        for (unsigned int i = 0; i < ulNodeNum; ++i) {
            pstStu = ppstStus[i];
            list_add(&(pstStu->stNode), pstHead);
        }
    }
}

void DL_BatchCreateNodes(struct Stu **ppstStus, unsigned int ulNodeNum, unsigned int ulStartId) {
    assert(NULL != ppstStus);
    for (unsigned int i = 0; i < ulNodeNum; ++i) {
        ppstStus[i] = (struct Stu *) malloc(sizeof(struct Stu));
        assert(NULL != ppstStus[i]);
        ppstStus[i]->ulId = ulStartId;
        DL_PrintNode("create", ppstStus[i]);
        ulStartId++;
    }
}

// 从给定的元素开始遍历,包括给定的元素
void DL_IterateIncludeGivenEntry(struct list_head *pstHead, struct Stu *pstStu, int lReverse) {
    assert((NULL != pstHead) && (NULL != pstStu));
    struct Stu *pstNextStu = NULL;
    if (lReverse) {
        list_for_each_entry_from_reverse(pstStu, pstHead, stNode) {
            DL_PrintNode("show backward", pstStu);
        }
    } else {
        list_for_each_entry_safe_from(pstStu, pstNextStu, pstHead, stNode) {
            DL_PrintNode("show forward", pstStu);
        }
    }
}

// 从给定的元素开始遍历，
void DL_IterateExcludeGivenEntry(struct list_head *pstHead, struct Stu *pstStu, int lReverse) {
    assert((NULL != pstHead) && (NULL != pstStu));
    struct Stu *pstNextStu = NULL;
    if (lReverse) {
        list_for_each_entry_continue_reverse(pstStu, pstHead, stNode) {
            DL_PrintNode("show backward", pstStu);
        }
    } else {
        list_for_each_entry_safe_continue(pstStu, pstNextStu, pstHead, stNode) {
            DL_PrintNode("show forward", pstStu);
        }
    }
}

void DL_CreateNoEmptyList(struct list_head *pstHead, unsigned int ulNodeNum) {
    assert((NULL != pstHead) && (0 != ulNodeNum));
    struct Stu **ppstStus = NULL;

    ppstStus = (struct Stu **) malloc(sizeof(struct Stu *) * ulNodeNum);
    assert(NULL != ppstStus);

    INIT_LIST_HEAD(pstHead);
    DL_BatchCreateNodes(ppstStus, ulNodeNum, 0);
    DL_BatchAddStuLiNodes(pstHead, ppstStus, ulNodeNum, 1);
    free((void *) ppstStus);
}

/**********************************************************************************************************************/
void DL_IterateGivenPoint() {
    // 分配空间
    struct Stu *apstStus[MAX_ELE_NUMS] = {0};
    DL_BatchCreateNodes(apstStus, MAX_ELE_NUMS, 0);

    // 初始化链表
    struct StuList stList = {0};
    INIT_LIST_HEAD(&(stList.stLi));

    // 链表尾部添加
    DL_BatchAddStuLiNodes(&(stList.stLi), apstStus, MAX_ELE_NUMS, 1);

    //DL_IterateIncludeGivenEntry(&(stList.stLi), apstStus[2], 1);
    DL_IterateExcludeGivenEntry(&(stList.stLi), apstStus[2], 1);

    // 释放链表所有数据
    DL_ClearStuLi(&(stList.stLi));
}

// 简单使用
void DL_Basic() {
    // 分配空间
    struct Stu *apstStus[MAX_ELE_NUMS] = {0};
    DL_BatchCreateNodes(apstStus, MAX_ELE_NUMS, 0);

    // 初始化链表
    struct StuList stList = {0};
    INIT_LIST_HEAD(&(stList.stLi));

    // 无数据，为空
    printf("init, "
           "list emtpy: %s"
           "\n",
           list_empty(&(stList.stLi)) ? "yes" : "no");

    // 链表尾部添加
    DL_BatchAddStuLiNodes(&(stList.stLi), apstStus, MAX_ELE_NUMS, 1);

    // 有数据不为空
    printf("After Add, "
           "list emtpy: %s"
           "\n",
           list_empty(&(stList.stLi)) ? "yes" : "no");

    struct Stu *pstStu = NULL;
    struct list_head *pstNode = NULL;
    struct list_head *pstNextNode = NULL;

    // 打印所有的链表数据
    DL_PrintStuLi(&(stList.stLi), 0);

    // 释放链表所有数据
    DL_ClearStuLi(&(stList.stLi));
}

void showBasicListInfo() {
    struct Stu *apstStus[MAX_ELE_NUMS] = {0};
    DL_BatchCreateNodes(apstStus, MAX_ELE_NUMS, 0);

    // init list
    struct StuList stList = {0};
    INIT_LIST_HEAD(&(stList.stLi));

    // no data, is empty
    printf("init, "
           "list emtpy: %s"
           "\n",
           list_empty(&(stList.stLi)) ? "yes" : "no");

    // add node to list tail
    for (unsigned int i = 0; i < MAX_ELE_NUMS; ++i) {
        list_add_tail(&(apstStus[i]->stNode), &(stList.stLi));
        printf("list empty: %s, "
               "list singular: %s, "
               "list first: %s, "
               "list last: %s, "
               "entry is head: %s "
               "\n",
               list_empty(&(stList.stLi)) ? "yes" : "no",
               list_is_singular(&(stList.stLi)) ? "yes" : "no",
               list_is_first(&(apstStus[i]->stNode), &(stList.stLi)) ? "yes" : "no",
               list_is_last(&(apstStus[i]->stNode), &(stList.stLi)) ? "yes" : "no",
               list_entry_is_head(apstStus[i], &(stList.stLi), stNode) ? "yes" : "no"
        );
    }

    printf("list first: %u"
           "list last: %u"
           "\n",
           list_first_entry_or_null(&(stList.stLi), struct Stu, stNode)->ulId,
           list_last_entry(&(stList.stLi), struct Stu, stNode)->ulId
    );
    DL_PrintStuLi(&(stList.stLi), 0);
    DL_ClearStuLi(&(stList.stLi));
}

struct InvalidStruct {
    int ulInteger;
    unsigned long long dulDoubleInteger;
    char szName[20];
    float fDataFloat;
};
int main() {

    showBasicListInfo();

    return 0;
}
