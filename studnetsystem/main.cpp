#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#define LEN sizeof(LNode)
using namespace std;
int seat;     //ͨѶ¼��Ա�����

typedef struct LNode
{
    int number;
    double telenum;
    char name[20];
    char street[20];
    char city[20];
    int eip;
    char country[20];
    struct LNode *next;
} LNode,*LinkList;
//����ͨѶ¼���

void printList(LinkList L)
{
    // ��ӡͷ����ַΪL��ͨѶ¼
    printf("\n          --------------------------------------------------------------------------------------------\n");
    printf("               ѧ��       ����     �绰����         ����          ����          �ֵ�             �ʱ�\n");
    printf("          ----------------------------------------------------------------------------------------------\n");
    LinkList p=L;
    int n=1;
    if(L==NULL||L->next==NULL) printf("��ͨѶ¼��û��Ԫ��\n");
    else
        while(p->next !=NULL)
        {
            printf("          %2d   %-9d",n,p->next->number);
            printf("    %-5s  %.0f  %8s  %12s  %13s  %14d\n",p->next->name,p->next->telenum,p->next->country,p->next->city,p->next->street,p->next->eip);
            p=p->next;
            n++;
        }
    printf("          ---------------------------------------------------------------------------------------------\n");
    return ;
}

LinkList prior(LinkList L,LinkList p)  //��ȡ��ǰԪ�ص�ǰһ��Ԫ�صĵ�ַ
{
    if(L->next==NULL) return(L);  //����һ���ڵ��,����ͷ���
    LinkList p_prior=L;
    while(p_prior->next != p)  //��һ���ڵ��p����ʱ
    {
        p_prior=p_prior->next;
    }
    return (p_prior);
}

void insertYouXu(LinkList L,LinkList Elem)
{
    //����һ��Ԫ�أ�ʹԭ�������Ϊ����
    LinkList p=L->next;    //p��һ���ڵ�
    while(p!=NULL && Elem->number>=p->number)
    {
        if(p->number==Elem->number)
        {
            printf("�ظ����룡��\n");
            return;
        }
        p=p->next;
    }         //ȷ��Elem�����λ��
    if(p==NULL)
    {
        p=prior(L,p);
        Elem->next=NULL;
        p->next=Elem;
    }
    else       //��Ϊ�ձ��嵽ͷ���֮��
    {
        p=prior(L,p);
        Elem->next=p->next;
        p->next=Elem;
    }
}

LinkList creatIncreLink()
{
    LinkList L=(LinkList)malloc(LEN);  //ͷ���
    L->next=NULL;
    LinkList p;
    int num=1;

    int number;
    double telenum;
    char name[20];
    char country[20];
    char city[20];
    char street[20];
    int eip;
    printf("������ѧ��ѧ�š������͵绰���룬����ͨѶ¼����'-1'Ϊ���������־\n");
    printf("������ѧ�� %d��",num);
    cin>>number;
    printf("���������� %d: ",num);
    cin>>name;
    printf("������绰���� %d��",num);
    cin>>telenum;
    printf("��������� %d��",num);
    cin>>country;
    printf("��������� %d��",num);
    cin>>city;
    printf("������ֵ� %d��",num);
    cin>>street;
    printf("�������ʱ� %d��",num);
    cin>>eip;
    while (number>=0)  //��-1λ������־
    {
        p=(LinkList)malloc(LEN); //�½��
        p->number=number;
        p->telenum=telenum;
        strcpy(p->name,name); //��name���Ƶ�p->name
        strcpy(p->country,country);
        strcpy(p->city,city);
        strcpy(p->street,street);
        p->eip=eip;
        insertYouXu(L,p);       //����Ĳ����½��
        num++;                  //num++����ڶ���ѧ������Ϣ
        printf("������ѧ�� %d��",num);
        scanf("%d",&number);
        printf("���������� %d: ",num);
        cin>>name;
        printf("������绰���� %d��",num);
        cin>>telenum;
        printf("��������� %d��",num);
        cin>>country;
        printf("��������� %d��",num);
        cin>>city;
        printf("������ֵ� %d��",num);
        cin>>street;
        printf("�������ʱ� %d��",num);
        cin>>eip;
    }
    return(L);
}


void deleteElem(LinkList L,int i)       //��ͨѶ¼��ɾ����i��Ԫ��
{
    LinkList p=L;
    int j=0;
    while (p->next&&j<i-1)
    {
        p = p->next;
        j++;
    }
    if(!(p->next)) //�����һ���ڵ㲻����,��
    {
        printf("��%d��Ԫ��ɾ��ʧ��\n",i);
        return ;
    }

    LinkList q = p->next;
    p->next = q->next;
    free(q);
}

int searchNum(LinkList L,int n)
{
    // ��ѧ�Ų���ͨѶ��
    int flag=0;
    LinkList p=L->next;
    seat=1;
    if(L->next==NULL) printf("��������û��Ԫ��,����ʧ��\n");
    else
    {
        while(p !=NULL)
        {
            if(p->number<=n)
                if(p->number==n)
                {
                    flag=1;
                    printf("Ҫ���ҵ��ǵ�%dλͨѶ�ߣ�\n",seat);
                    printf("                        ѧ��: %d   ����: %s   �绰����.:%.0f  ����:%s  ����:%s  �ֵ�:%s  �ʱ�:%d\n",p->number,p->name,p->telenum,p->country,p->city,p->street,p->eip);
                }
            p=p->next;
            seat++;//!!!!
        }
    }
    return flag;
}

int searchName(LinkList L,char n[])
{
    int flag=0;     //����һ����־,���Ƿ�ƥ��
    LinkList p=L->next;
    seat=1;
    if(L->next==NULL||L==NULL)   //��һ���ڵ�ջ��������
        printf("��ͨѶ¼��û��Ԫ��,����ʧ��\n");
    else
    {
        while(p !=NULL)
        {
            if(!strcmp(p->name,n))  //�Ƚ�p->name�������n,��ͬ����0,
            {
                flag=1;            //��־ƥ��ɹ�
                printf("Ҫ���ҵ��ǵ�%dλͨѶ�ߣ�\n",seat);
                printf("                        Number: %d   Name: %s   TeleNo.:%.0f Country: %s  City: %s  Street: %s  eip: %d\n",p->number,p->name,p->telenum,p->country,p->city,p->street,p->eip);
            }
            p=p->next;
            seat++;
        }
    }
    return flag;
}

int delNum(LinkList L,int n)
{
    // ��ѧ��ɾ��ͨѶ��
    int flag=0;
    LinkList p=L->next;
    seat=1;
    if(L->next==NULL)
        printf("��������û��Ԫ��,ɾ��ʧ��\n");
    else
    {
        while(p !=NULL)
        {
            if(p->number<=n)
            {
                if(p->number==n)
                {
                    flag=1;
                    printf("%d ",p->number);
                    p=p->next;
                    deleteElem(L,seat);

                }
            }
            else
            {
                p=p->next;
                seat++;
            }
        }
        printf("��ɾ��\n");
    }
    return flag;
}


int delName(LinkList L,char n[])
{
    // ������ɾ��ͨѶ��
    int flag=0;
    LinkList p=L->next;  //pΪ��һ���ڵ�
    seat=1;
    if(L->next==NULL)
        printf("��������û��Ԫ��,����ʧ��\n");
    else
    {
        while(p !=NULL)
        {
            if(!strcmp(p->name,n))
            {
                flag=1;
                printf("%s ",p->name); //���ƥ�䵽��,�����xxx��ɾ��
                p=p->next;
                deleteElem(L,seat);
            }
            else
            {
                p=p->next;
                seat++;
            }
        }
        if(flag)printf("��ɾ��\n");
    }
    return flag;
}

void write(LinkList L)
{
    ofstream output("test.txt"); //�����������ļ����й���
    LinkList p=L;
    while(p->next !=NULL)
    {
        output<<p->next->number<<setw(10)<<p->next->name<<setw(12)<<p->next->telenum<<setw(10)<<p->next->country<<setw(16)<<p->next->city<<setw(20)<<p->next->street<<setw(20)<<p->next->eip<<endl;
        p = p->next;
    }
}


void read(string file) //���ж���
{
    ifstream ifs;  //�����������ļ����й���
    ifs.open(file.data());   //���ļ����������ļ���������
    string s;
    while(getline(ifs,s))
    {
        cout<<s<<endl;
    }
    ifs.close();
}
int main(void)
{
//system("color 1f");
    LinkList L=NULL;
    printf("\n           ***************** ^@^��ӭʹ��ͨѶ¼ϵͳ***********\n");
    printf("           *               1 ͨѶ¼�Ľ���                   *\n");
    printf("           *               2 ����ͨѶ��¼                   *\n");
    printf("           *               3 ��ѯͨѶ��¼                   *\n");
    printf("           *               4 ɾ��ͨѶ��¼                   *\n");
    printf("           *               5 ��ʾͨѶ¼��Ϣ                 *\n");
    printf("           *               6 ����Ϣд���ļ�                 *\n");
    printf("           *               7 ��ȡ�ļ�����                   *\n");
    printf("           *               0 �˳�����ϵͳ                   *\n");
    printf("           **************** ^@^��ӭʹ��ͨѶ¼ϵͳ************\n");
    int flag=0;
    int menu;
    printf("��ѡ��0-5��");
    scanf("%d",&menu);
    while(menu!=0)
    {
        switch(menu)
        {
        case 1:
        {
            L=creatIncreLink();
            printf("����ͨѶ¼��");
            printList(L);
            flag=1;
            break;
        }
        case 2:
        {
            if(flag==1)
            {
                int number,telenum;
                char name[20];
                char country[20];
                char city[20];
                char street[20];
                int eip;
                printf("������ͨѶ�ߵ�ѧ�ź�������\n");
                printf("������ѧ��: ");
                cin>>number;
                printf("����������: ");
                cin>>name;
                printf("������绰����: ");
                cin>>telenum;
                printf("��������ң�");
                cin>>country;
                printf("��������У�");
                cin>>city;
                printf("������ֵ���");
                cin>>street;
                printf("�������ʱࣺ");
                cin>>eip;

                LinkList p=(LinkList)malloc(LEN); //�½��
                p->number=number;
                strcpy(p->name,name);
                strcpy(p->country,country);
                strcpy(p->city,city);
                strcpy(p->street,street);
                p->eip = eip;
                p->telenum=telenum;
                insertYouXu(L,p);       //����Ĳ����½��
                printf("�����");
                printList(L);
            }
            else printf("\nERROR: ͨѶ¼��û�н��������Ƚ���ͨѶ¼\n");
            break;
        }
        case 3:
        {
            int way,n;
            char na[20];
            int s;
            if(L!=NULL)
            {
                if(flag)
                {
                    printf("ѡ����ҷ�ʽ��\n");
                    printf("               1.��ѧ��   2.������");
                    scanf("%d",&way);
                    if(way==1)
                    {
                        printf("\n������ѧ��:");
                        scanf("%d",&n);
                        s=searchNum(L,n);
                        if(s==0) printf("�޴�ͨѶ�ߣ�����ʧ�ܣ�\n");
                    }
                    else if(way==2)
                    {
                        printf("\n����������:");
                        cin>>na;
                        s=searchName(L,na);
                        if(s==0) printf("�޴�ͨѶ�ߣ�����ʧ�ܣ�\n");
                    }
                    else printf("ͨѶ¼���޼�¼��\n");
                }
                break;
            }
            else printf("ͨѶ¼���޼�¼��\n");
            break;
        }
        case 4:
        {
            int way;
            printf("ѡ��ɾ����ʽ��1.�����  2. ��ѧ��  3.������ \n");
            scanf("%d",&way);
            if(way==1)
            {
                int n;
                printf("������ͨѶ¼���: ");
                cin>>n;
                printf("ɾ����\n");
                deleteElem(L,n);
                printList(L);
            }
            else if(way==2)
            {
                int n,f;
                printf("������ѧ��: ");
                cin>>n;
                f=delNum(L,n);
                if(f!=0)
                {
                    printf("ɾ����\n");
                    printList(L);
                }
                else printf("�޸�ѧ�ţ�ɾ��ʧ��!\n");
            }
            else if(way==3)
            {
                char na[20];
                int f;
                printf("\n����������:");
                cin>>na;
                f=delName(L,na);
                if(f!=0)
                {
                    printf("ɾ����\n");
                    printList(L);
                }
                else printf("�޸�ѧ�ţ�ɾ��ʧ��!\n");
            }
            else printf("ERROR!!\n");
            break;
        }
        case 5:
        {
            printf("��ǰͨѶ¼�������£�\n");
            printList(L);
            break;
        }
        case 0:
            exit(0);
        default:
            printf("\nû�д˹��ܣ���������\n");
        case 6:
        {
            LinkList p=L;
            write(L);
            printf("д���ļ��ɹ�\n");
            break;
        }
        case 7:
        {
            printf("�ļ�ͨѶ¼��Ϣ:\n");
            read("test.txt");
            break;
        }
        }
        printf("ѡ���ܣ�");
        scanf("%d",&menu);
    }
}
