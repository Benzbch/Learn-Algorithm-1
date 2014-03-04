#include <iostream>
#include<algorithm>
#include <cstdlib>
#include<stdio.h>
using namespace std;
typedef struct AVLNode{
	int key,bf;
	AVLNode *lchild,*rchild;
}AVLNode,*AVLTree;
void L_Roate(AVLNode **p)//��*pָ��Ľ������֮���ƶ�*pָ��ָ���µĸ����
{
	AVLNode *q=(*p)->rchild;
	(*p)->rchild=q->lchild;
	q->lchild=*p;
	*p=q;
}
void R_Roate(AVLNode **p)//��*pָ��Ľ���ҵ���֮���ƶ�*pָ��ָ���µĸ����
{
	AVLNode *q=(*p)->lchild;
	(*p)->lchild=q->rchild;
	q->rchild=*p;
	*p=q;
}
void leftbalance(AVLNode **p)//��*pָ��Ľ����ƽ����ת֮���ƶ�*pָ��ָ���µĸ����
{
	AVLNode *lp=(*p)->lchild,*rd;
	switch(lp->bf)
	{
	case 1:
		(*p)->bf=lp->bf=0;
		R_Roate(p);
		break;
	case 0:
		(*p)->bf=1;
		break;
	case -1:
		rd=lp->rchild;
		switch(rd->bf)
		{
		case 1:
			(*p)->bf=-1;
			lp->bf=0;
			break;
		case 0:
			(*p)->bf=lp->bf=0;
			break;
		case -1:
			(*p)->bf=0;
			lp->bf=1;
			break;
		}
		rd->bf=0;
		L_Roate(&(*p)->lchild);
		R_Roate(p);
	}
}
void rightbalance(AVLNode **p)//��*pָ��Ľ����ƽ����ת֮���ƶ�*pָ��ָ���µĸ����
{
	AVLNode *rp=(*p)->rchild,*ld;
	switch(rp->bf)
	{
	case 1:
		(*p)->bf=rp->bf=0;
		L_Roate(p);
		break;
	case 0:
		(*p)->bf=1;
		break;
	case -1:
		ld=rp->lchild;
		switch(ld->bf)
		{
		case 1:
			(*p)->bf=0;
			rp->bf=1;
			break;
		case 0:
			(*p)->bf=rp->bf=0;
			break;
		case -1:
			(*p)->bf=-1;
			rp->bf=0;
			break;
		}
		ld->bf=0;
		R_Roate(&(*p)->rchild);
		L_Roate(p);
	}
}
int insertAVL(AVLNode **t,int e,bool *taller)//�����в�������e��ͬ�Ľ�������e����1�����򷵻�0���ڲ�����������ƽ�⴦��
{
	if(!(*t))
	{
		*t=new AVLNode();
		(*t)->key=e;
		(*t)->lchild=(*t)->rchild=NULL;
		(*t)->bf=0;
	}
	else{
		if(e==(*t)->key)
			return 0;
		if(e<(*t)->key)
		{
			if(insertAVL(&((*t)->lchild),e,taller)==0)
				return 0;
			if(*taller)
			{
				switch((*t)->bf)
				{
				case 1:
					leftbalance(t);
					*taller=false;
					break;
				case 0:
					(*t)->bf=1;
					*taller=true;
					break;
				case -1:
					(*t)->bf=0;
					*taller=false;
					break;
				}
			}
		}
		else{
			if(insertAVL(&((*t)->rchild),e,taller)==0)
				return 0;
			if(*taller)
			{
				switch((*t)->bf)
				{
				case 1:
					(*t)->bf=0;
					*taller=false;
					break;
				case 0:
					(*t)->bf=-1;
					*taller=true;
					break;
				case -1:
					rightbalance(t);
					*taller=false;
					break;
				}
			}
		}
	}
	if(!(*t))
		return 1;
}
bool search(AVLNode *T,int key,AVLNode **p,AVLNode **q)
{
	if(T==NULL)
	{
		*q=*p;
		return false;
	}
	if(T->key==key)
	{
		*p=T;
		return true;
	}
	else if(T->key>key)
	{
		*q=T;
		return search(T->lchild,key,p,q);
	}
	else if(T->key<key)
	{
		*q=T;
		return search(T->rchild,key,p,q);
	}
}
bool del(AVLNode *T,int key)//������ϴ�һ��
{
	AVLNode *pp=new AVLNode(),*qq=new AVLNode();
	AVLNode **p=&pp,**q=&qq;
	if(!search(T,key,p,q))
		return false;
	if((*p)->lchild==NULL&&(*p)->rchild==NULL)
		delete (*p);
	else if(!((*p)->lchild!=NULL&&(*p)->rchild!=NULL))
	{
		if((*p)->lchild==NULL)
		{
			if(*p==(*q)->rchild)
				(*q)->rchild=(*p)->rchild;
			else
				(*q)->lchild=(*p)->rchild;
		}
		else{
			if(*p==(*q)->rchild)
				(*q)->rchild=(*p)->lchild;
			else
				(*q)->lchild=(*p)->lchild;
		}
		delete (*p);
	}
	else{
		AVLNode *m=*p,*n=(*p)->lchild;
		while(n->rchild!=NULL)
		{
			m=n;
			n=n->rchild;
		}
		(*p)->key=n->key;
		if(m!=*p)
			m->lchild=n->lchild;
		else
			m->lchild=n->lchild;
		delete n;
	}
}
void inOrder(AVLNode *T)
{
	if(T!=NULL)
	{
		inOrder(T->lchild);
		printf("%d ",T->key);
		inOrder(T->rchild);
	}
}
void creat(AVLNode *T,int *num,int len)
{
	bool b=true,*taller;
	taller=&b;
	if(len==0)
		return;
	T->key=num[0];
	T->lchild=T->rchild=NULL;
	for(int i=1;i<len;i++)
		insertAVL(&T,num[i],taller);
}
int main()
{
	int len=8,num[8]={4,3,5,1,2,6,7,8};
	AVLNode *T=new AVLNode(),*pp=new AVLNode(),*qq=new AVLNode();
	AVLNode **p=&pp,**q=&qq;
	creat(T,num,len);
	cout<<"4,3,5,1,2,6,7,8"<<endl<<"inOrder:"<<endl;
	inOrder(T);
	cout<<endl<<"Delete 5:"<<endl;
	del(T,5);
	inOrder(T);
	return 0;
}