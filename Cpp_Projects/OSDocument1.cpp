#include <iostream>
#include <stdlib.h>
#include <string>
#include <iomanip>
using namespace std;

struct PCB
{
    string name = "";
    string state = "W";
    int needtime = 0;
    int cputime = 0;
    int prio = 0;
    int round = 0;
    struct PCB *next = NULL;
};
//
//PCB* Node = new PCB;
PCB *finish = new PCB;
PCB *head = new PCB;
PCB *run = new PCB;
//PCB* Temp = new PCB;
PCB *ready = new PCB;
PCB *tail = new PCB;
// ��ָ���ʼ��ΪNULL?
PCB *create(int, int); // ���ڴ������̣�ͷ�巨��

bool insert1(PCB *); // ���������Ⱦ�����������

bool insert2(PCB *); // ʱ��Ƭ��ת���Ⱦ�����������

PCB *firstin(PCB *, int); // ���Ⱦ������е�һ������Ͷ������

void print(PCB *, PCB *, int); // ÿ�����н��̺��ӡ����״̬

void prisch(); // �����������㷨

void roundsch(); // ʱ��Ƭ��ת�����㷨

void announce(); // ϵͳ������ʽ

void clearAllP(); //  ���ָ��

PCB *create(int n, int r)
{

    //PCB* head = new PCB;

    head->next = NULL; // ��ʼ��ͷ���
    if (n > 0)
    {
        cout << "׼������" << n << "����" << endl;
        string pname;
        int time;
        for (int counter = 1; counter < n + 1; counter++)
        {
            // ͷ�巨������������
            cout << "���ڴ�����" << counter << "������" << endl;
            cout << "�����������(string)��";
            cin >> pname;
            cout << "���������Ҫʱ��(int)��";
            cin >> time;
            PCB *Node = new PCB;
            Node->name = pname;
            Node->needtime = time;
            //Node->cputime = 0;
            Node->next = head->next;
            Node->prio = 50 - Node->needtime;
            Node->round = r; // ����ʱ��ƬΪһ����λ
            //Node->state = "W";
            head->next = Node;
            ////delete(Node);
            Node = NULL;
        }
    }
    else // �ж�����������Ƿ�Ϊ����
    {
        cout << "�������Ƿ��������ԣ�" << endl;
        int nn = 0;
        cout << "��������ȷ�Ĵ�������";
        cin >> nn; // new num(nn)
        create(nn, r);
    }
    /*
    * //delete(Node);
    * Node = NULL;
    * Node = new PCB;
    */
    return head;
}

bool insert1(PCB *head)
{
    if (head->next != NULL)
    {
        int length = 1;
        PCB *Temp = head->next;
        while (Temp->next != NULL)
        {
            length++;
            Temp = Temp->next;
        }
        for (int i = 1; i < length; i++)
        {
            Temp = head->next;

            while (Temp->next != NULL)
            {
                if (Temp->prio >= Temp->next->prio)
                {
                    Temp = Temp->next;
                }
                else /* if (Temp->prio < Temp->next->prio)*/
                {
                    // ��ֵ��󴫡�
                    PCB *tp = new PCB; // ��ʱPCBָ��
                    tp->cputime = Temp->cputime;
                    tp->name = Temp->name;
                    tp->needtime = Temp->needtime;
                    tp->prio = Temp->prio;
                    tp->round = Temp->round;
                    tp->state = Temp->state;

                    Temp->cputime = Temp->next->cputime;
                    Temp->name = Temp->next->name;
                    Temp->needtime = Temp->next->needtime;
                    Temp->prio = Temp->next->prio;
                    Temp->round = Temp->next->round;
                    Temp->state = Temp->next->state;

                    Temp->next->cputime = tp->cputime;
                    Temp->next->name = tp->name;
                    Temp->next->needtime = tp->needtime;
                    Temp->next->prio = tp->prio;
                    Temp->next->round = tp->round;
                    Temp->next->state = tp->state;

                    //Temp = Temp->next;
                    ////delete (tp); // �����ʱָ��
                    tp = NULL; // �ÿ�ָ��
                    Temp = Temp->next;
                }
            }
        }
        ready = head->next;
        tail = Temp;
        /*
        * //delete(Temp);
        * Temp = NULL;
        * Temp = new PCB;
        */
        return true;
    }
    else
    {
        cout << "�����������޽���" << endl;
        return false;
    }
}

bool insert2(PCB *head)
{
    if (head->next != NULL)
    {
        PCB *Temp = head->next;
        if (Temp->needtime > 0)
        {
            while (Temp->next != NULL)
            {
                Temp = Temp->next;
            }
            tail = Temp;
            PCB *p = head->next; // ��ʱָ��
            head->next = p->next;
            p->next = NULL;
            tail->next = p;
            ready = head->next;
            tail = p;
            ////delete (p); // ȥ����ʱָ��
            p = NULL; // �ÿ�ָ��
        }
        /*
        * //delete (Temp);
        * Temp = NULL;
        * Temp = new PCB;
        */
        return true;
    }
    else
    {
        cout << "��������û�н�����" << endl;
        return false;
    }
}

PCB *firstin(PCB *head, int op)
{
    run = ready;
    if (op == 1)
    {
        if (ready != tail)
        {
            if (run->needtime > 0)
            {
                cout << "��ǰͶ�����еĽ���Ϊ��" << run->name << endl;
                cout << "����ִ��ǰ״̬" << endl;
                run->state = "R";
                cout << "��ǰ���������С�" << endl;
                print(head, finish, 1);
                run->cputime++;
                run->needtime--;
                run->prio = 50 - run->needtime;
                // δ��ɵĽ��̷��ؾ������еĶ�β��������һ������
                head->next = run->next;
                run->state = "W";
                run->next = NULL;
                tail->next = run;
                /*
                * PCB* b = new PCB;// ��ʱָ��
                * b = Temp;// ���þ�������βָ��
                * b->next = run;
                * //delete(b);// �����ʱָ��
                * b = NULL;// �ÿ�ָ��
                */
            }
            else if (finish->state == "R") // �ж��Ƿ��н����Ѿ���ɣ�ֻ�е�һ���н������ʱ��������������
            {
                head->next = run->next;
                run->state = "F";
                run->next = NULL;
                finish = run;
            }
            else
            {
                // β�巨��finish����������ɵĽ���
                head->next = run->next;
                run->state = "F";
                run->next = NULL;
                PCB *Temp = finish;
                while (Temp->next != NULL)
                {
                    Temp = Temp->next;
                }
                //PCB* b =Temp; // �ҵ��ϴ���ɵĽ�����βָ�롣
                Temp->next = run;
                ////delete (b);
            }
        }
        else if (ready == tail)
        {
            cout << "��ǰ�������н�ʣ��һ������(" << run->name << ")�ڵ���" << endl;
            cout << "����ִ��ǰ״̬" << endl;
            cout << "����(" << run->name << ")����������" << run->needtime << "��" << endl;
            run->state = "R";
            cout << "ִ�����!" << endl;
            print(head, finish, 1);

            run->cputime += run->needtime;
            run->needtime = 0;
            run->prio = 50;
            head->next = run->next;
            run->state = "F";
            run->next = NULL;
            PCB *Temp = finish;
            while (Temp->next != NULL)
            {
                Temp = Temp->next;
            }
            //PCB* b = Temp; // �ҵ��ϴ���ɵĽ�����βָ�롣
            Temp->next = run;
        }
    }
    else
    {
        if (ready != tail)
        {
            if (run->needtime > 1) // ��С��λ������ʱ��Ƭ��С��1ʱ����������һ������Ͷ�����
            {
                cout << "��ǰͶ�����еĽ���Ϊ��" << run->name << endl;
                cout << "����ִ��ǰ״̬" << endl;
                run->state = "R";
                cout << "��ǰ���������С�" << endl;
                print(head, finish, 2);
                run->cputime += run->round;
                run->needtime -= run->round;
                run->prio = 50 - run->needtime;
                // δ��ɵĽ��̷��ؾ������еĶ�β��������һ������
                head->next = run->next;
                run->state = "W";
                run->next = NULL;
                tail->next = run;
            }
            else if (run->needtime == 1 && finish->state == "R")
            {
                cout << "��ǰͶ�����еĽ���Ϊ��" << run->name << "��" << run->next->name << endl;
                cout << "����ִ��ǰ״̬" << endl;
                run->next->state = "R";
                run->state = "R";
                cout << "��ǰ���������С�" << endl;
                print(head, finish, 2);
                run->cputime++;
                run->next->cputime++;
                run->needtime--;
                run->next->needtime--;
                run->prio = 50 - run->needtime;
                // δ��ɵĽ��̷��ؾ������еĶ�β��������һ������
                head->next = run->next->next;
                run->state = "F";
                run->next = NULL;
                finish->state = "F";
                finish->next = run;
            }
            else if (finish->state == "R")
            {
                head->next = run->next;
                run->state = "F";
                run->next = NULL;
                finish->state = "F";
                finish->next = run;
            }
            else
            {
                // β�巨��finish����������ɵĽ���
                head->next = run->next;
                run->state = "F";
                run->next = NULL;
                PCB *Temp = finish->next;
                while (Temp->next != NULL)
                {
                    Temp = Temp->next;
                }
                //PCB* b = Temp; // �ҵ��ϴ���ɵĽ�����βָ�롣
                Temp->next = run;
                /*
                * //delete(Temp);
                * Temp = NULL;
                * Temp = new PCB;
                */
            }
        }
        else if (ready == tail)
        {
            cout << "��ǰ�������н�ʣ��һ������(" << run->name << ")�ڵ���" << endl;
            cout << "����ִ��ǰ״̬" << endl;
            run->state = "R";
            cout << "ִ�����!" << endl;
            print(head, finish, 2);
            int a = run->needtime % run->round; // �ж��Ƿ�������2
            int b = run->needtime / run->round;
            // ����ȡ��
            //b = (run->needtime + run->round - 1) / run->round;
            b = a > 0 ? b + 1 : b;
            cout << "����(" << run->name << ")������ѭ������" << b << "��" << endl;
            run->cputime += run->needtime;
            run->needtime = 0;
            run->prio = 50;
            head->next = NULL;
            run->next = NULL;
            run->state = "F";
            PCB *Temp = finish;
            while (Temp->next != NULL)
            {
                Temp = Temp->next;
            }
            // �ҵ��ϴ���ɵĽ�����βָ�롣
            Temp->next = run;
        }
        /*
        * //delete(Temp);
        * Temp=NULL;
        * Temp = new PCB;
        */
    }
    /*
    * //delete(run);
    * run = NULL;
    * run = new PCB;
    */
    return finish;
}

void print(PCB *head, PCB *finish, int op)
{
    if (op == 1)
    {
        cout << "--------------------------����״̬��------------------------------" << endl;
        cout << setw(8) << "������"
             << "|" << setw(18) << "��ռ��CPUʱ��Ƭ��"
             << "|" << setw(10) << "ʣ��ʱ��"
             << "|" << setw(10) << "��ǰ������"
             << "|" << setw(15) << "��ǰ����״̬"
             << "|" << endl;
        cout << setw(8) << "name"
             << "|" << setw(18) << "cputime"
             << "|" << setw(10) << "needtime"
             << "|" << setw(10) << "priority"
             << "|" << setw(15) << "state"
             << "|" << endl;
        PCB *Temp = head->next;
        PCB *Node = finish->next;
        while (Temp != NULL)
        {
            //cout << 11111111111 << endl;
            cout << setw(8) << Temp->name << "|" << setw(18) << Temp->cputime << "|" << setw(10) << Temp->needtime << "|" << setw(10) << Temp->prio << "|" << setw(15) << Temp->state << "|" << endl;
            Temp = Temp->next;
        }
        /*
        * //delete(Temp);
        * Temp = NULL;
        * Temp = new PCB;
        */
        if (finish->state == "F")
        {
            // ���н���ǰ״̬��ΪR,֮���ٱ�
            while (Node != NULL)
            {
                cout << setw(8) << Node->name << "|" << setw(18) << Node->cputime << "|" << setw(10) << Node->needtime << "|" << setw(10) << Node->prio << "|" << setw(15) << Node->state << "|" << endl;
                Node = Node->next;

            } /* while (Temp == NULL);*/
        }
        else
        {
            cout << "��û�н�����ɣ�" << endl;
        }
    }
    else
    {
        cout << "--------------------------����״̬��------------------------------" << endl;
        cout << setw(8) << "������"
             << "|" << setw(18) << "��ռ��CPUʱ��Ƭ��"
             << "|" << setw(10) << "ʣ��ʱ��"
             << "|" << setw(10) << "ʱ��Ƭ"
             << "|" << setw(15) << "��ǰ����״̬"
             << "|" << endl;
        cout << setw(8) << "name"
             << "|" << setw(18) << "cputime"
             << "|" << setw(10) << "needtime"
             << "|" << setw(10) << "round"
             << "|" << setw(15) << "state"
             << "|" << endl;
        PCB *Temp = head->next;
        PCB *Node = finish;
        while (Temp != NULL)
        {
            cout << setw(8) << Temp->name << "|" << setw(18) << Temp->cputime << "|" << setw(10) << Temp->needtime << "|" << setw(10) << Temp->round << "|" << setw(15) << Temp->state << "|" << endl;
            Temp = Temp->next;
        }
        /*
        * //delete(Temp);
        * Temp = NULL;
        * Temp = new PCB;
        */
        if (Node->state == "F")
        {
            Temp = Node->next;
            // ���н���ǰ״̬��ΪR,֮���ٱ�
            /*while (Temp != NULL)*/
            do
            {
                if (Temp != NULL)
                {
                    cout << setw(8) << Temp->name << "|" << setw(18) << Temp->cputime << "|" << setw(10) << Temp->needtime << "|" << setw(10) << Temp->round << "|" << setw(15) << Temp->state << "|" << endl;
                    Temp = Temp->next;
                }
            } while (Temp == NULL);
        }
        else
        {
            cout << "��û�н�����ɣ�" << endl;
        }
    }
    /*
    * //delete(Node);
    * Node = NULL;
    * Node = new PCB;
    */
}

void prisch()
{
    int pn;
    cout << "�����봴�����̸�����";
    cin >> pn;
    PCB *pp = create(pn, 2);
    PCB *fp = new PCB; // ��ʱ���ָ��
    fp->next = NULL;
    fp->state = "R"; // �н��̵�һ����ɺ���û�Ϊ�Ǹ�����
    finish = fp;
    print(pp, fp, 1);
    bool judge = false;
    judge = insert1(pp);
    while (insert1(pp))
    {
        fp = firstin(pp, 1);
        print(pp, fp, 1);
        judge = insert1(pp);
    }
    ////delete (fp);
    fp = NULL;
}

void roundsch()
{
    int rr;
    /*
    * char choose;
    * cout << "�Ƿ�Ҫ����ʱ��Ƭ����" << "(y/n)";
    * cin >> choose;
    * if (choose == 'y' || choose == 'Y')
    * {
        //ʱ��Ƭ������ӦprintҲҪ�仯
    * } */
    cout << "������С��λʱ��Ƭ����";
    cin >> rr;
    int rn;
    cout << "�����봴�����̸�����";
    cin >> rn;
    PCB *rp = create(rn, rr);
    PCB *fp = new PCB; // ��ʱ���ָ��
    fp->next = NULL;
    fp->state = "R"; // �н��̵�һ����ɺ���û�Ϊ�Ǹ�����
    finish = fp;
    print(rp, fp, 2);
    bool judge = false;
    judge = insert2(rp);
    while (insert2(rp))
    {
        fp = firstin(rp, 2);
        print(rp, fp, 2);
        judge = insert2(rp);
    }
    ////delete (fp);
    fp = NULL;
}

void announce()
{
    int flag;
    cout << "-------------------------------------------------------------" << endl;
    cout << "----����ϵͳʵ����ʾ----��1805-3-20183584--������----" << endl;
    cout << "-----------------ʵ��һ--���̵���ģ���㷨-----------------" << endl;
    cout << "----------------------1.�����������㷨---------------------" << endl;
    cout << "----------------------2.ѭ����ת�����㷨-------------------" << endl;
    cout << "----------------------3.��ȫ�˳�----------------------------" << endl;
    cout << "��ѡ���Ӧ������ţ�";
    cin >> flag;
    switch (flag)
    {
    case 1:
        system("cls");
        cout << "�����������㷨�ɹ�����" << endl;
        prisch();
        announce();
        break;
    case 2:
        system("cls");
        cout << "ѭ����ת�����㷨�ɹ�����" << endl;
        roundsch();
        announce();
        break;
    case 3:
        cout << "ϵͳ�Ѱ�ȫ�˳�" << endl;
        break;
    default:
        break;
    }
}

void clearAllP()
{
    //Node = NULL;
    finish = NULL;
    head = NULL;
    run = NULL;
    //Temp = NULL;
    ready = NULL;
    tail = NULL;
    cout << "ָ����ȫ���ÿ�" << endl;
}

int main()
{
    announce();
    clearAllP();
    system("pause");
    return 0;
}
