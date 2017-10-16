 /* main2-4.c ��ѭ������,����bo2-4.c�������� */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-2.h"
 #include"bo2-4.c"

 Status compare(ElemType c1,ElemType c2)
 {
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 void visit(ElemType c)
 {
   printf("%d ",c);
 }

 void main()
 {
   LinkList L;
   ElemType e;
   int j;
   Status i;
   i=InitList_CL(&L); /* ��ʼ����ѭ������L */
   printf("��ʼ����ѭ������L i=%d (1:��ʼ���ɹ�)\n",i);
   i=ListEmpty_CL(L);
   printf("L�Ƿ�� i=%d(1:�� 0:��)\n",i);
   ListInsert_CL(&L,1,3); /* ��L�����β���3,5 */
   ListInsert_CL(&L,2,5);
   i=GetElem_CL(L,1,&e);
   j=ListLength_CL(L);
   printf("L������Ԫ�ظ���=%d,��1��Ԫ�ص�ֵΪ%d��\n",j,e);
   printf("L�е�����Ԫ������Ϊ��");
   ListTraverse_CL(L,visit);
   PriorElem_CL(L,5,&e); /* ��Ԫ��5��ǰ�� */
   printf("5ǰ���Ԫ�ص�ֵΪ%d��\n",e);
   NextElem_CL(L,3,&e); /* ��Ԫ��3�ĺ�� */
   printf("3�����Ԫ�ص�ֵΪ%d��\n",e);
   printf("L�Ƿ�� %d(1:�� 0:��)\n",ListEmpty_CL(L));
   j=LocateElem_CL(L,5,compare);
   if(j)
     printf("L�ĵ�%d��Ԫ��Ϊ5��\n",j);
   else
     printf("������ֵΪ5��Ԫ��\n");
   i=ListDelete_CL(&L,2,&e);
   printf("ɾ��L�ĵ�2��Ԫ�أ�\n");
   if(i)
   {
     printf("ɾ����Ԫ��ֵΪ%d,����L�е�����Ԫ������Ϊ��",e);
     ListTraverse_CL(L,visit);
   }
   else
     printf("ɾ�����ɹ���\n");
   printf("���L��%d(1: �ɹ�)\n",ClearList_CL(&L));
   printf("���L��L�Ƿ�գ�%d(1:�� 0:��)\n",ListEmpty_CL(L));
   printf("����L��%d(1: �ɹ�)\n",DestroyList_CL(&L));
 }