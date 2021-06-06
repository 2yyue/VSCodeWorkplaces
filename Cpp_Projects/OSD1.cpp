#include <iostream>
#include <stdlib.h>
#include <string>
#include <iomanip>
using namespace std;

typedef struct PCB
{
    string name = "";
    string state = "W";
    int needtime = 0;
    int cputime = 0;
    int prio = 0;
    int round = 0;
    struct PCB *next = NULL;
};

PCB *Node = new PCB;
PCB *finish = new PCB;
PCB *head = new PCB;
PCB *run = new PCB;
PCB *Temp = new PCB;
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
    /*
    * head = new PCB;
    * Node = new PCB;
    */
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
            Node->name = pname;
            Node->needtime = time;
            //Node->cputime = 0;
            Node->next = head->next;
            Node->prio = 50 - Node->needtime;
            Node->round = r; // ����ʱ��ƬΪһ����λ
            //Node->state = "W";
            head->next = Node;
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
    * delete(Node);
    * Node = NULL;
    * Node = new PCB;
    */
    return head;
}

bool insert1(PCB *head)
{
    if (head->next != NULL)
    {
        Temp = head->next;
        while (Temp->next != NULL)
        {
            while (Temp->prio >= Temp->next->prio)
            {
                Temp = Temp->next;
            }
            while (Temp->prio < Temp->next->prio)
            {
                // ��ֵ��󴫡�
                PCB *tp = new PCB; // ��ʱPCBָ��
                tp->cputime = Temp->cputime;
                tp->name = Temp->name;
                tp->needtime = Temp->needtime;
                tp->next = Temp->next;
                tp->prio = Temp->prio;
                tp->round = Temp->round;
                tp->state = Temp->state;
                Temp = Temp->next;
                Temp->next = tp;
                delete (tp); // �����ʱָ��
                tp = NULL;   // �ÿ�ָ��
                Temp = Temp->next;
            }
        }
        ready = head->next;
        tail = Temp;
        /*
        * delete(Temp);
        * Temp = NULL;
        * Temp = new PCB;
        */
        return 1;
    }
    else
    {
        cout << "�����������޽���" << endl;
        return 0;
    }
}

bool insert2(PCB *head)
{
    if (head->next != NULL)
    {
        Temp = head->next;
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
            delete (p); // ȥ����ʱָ��
            p = NULL;   // �ÿ�ָ��
        }
        /*
        * delete (Temp);
        * Temp = NULL;
        * Temp = new PCB;
        */
        return 1;
    }
    else
    {
        cout << "��������û�н�����" << endl;
        return 0;
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
                cout << "----------------------����ǰ����״̬--------------------------" << endl;
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
                cout << setw(8) << run->name << "|" << setw(18) << run->cputime << "|" << setw(10) << run->needtime << "|" << setw(10) << run->prio << "|" << setw(15) << run->state << "|" << endl;
                run->cputime++;
                run->needtime--;
                run->prio = 50 - run->needtime;
                run->state = "R";
                cout << "��ǰ���������С�" << endl;
                cout << setw(8) << run->name << "|" << setw(18) << run->cputime << "|" << setw(10) << run->needtime << "|" << setw(10) << run->prio << "|" << setw(15) << run->state << "|" << endl;
                // δ��ɵĽ��̷��ؾ������еĶ�β��������һ������
                head->next = run->next;
                run->state = "W";
                run->next = NULL;
                tail->next = run;
                /*
                * PCB* b = new PCB;// ��ʱָ��
                * b = Temp;// ���þ�������βָ��
                * b->next = run;
                * delete(b);// �����ʱָ��
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
                Temp = finish->next;
                while (Temp != NULL)
                {
                    Temp = Temp->next;
                }
                PCB *b = new PCB; // ��ʱָ��
                b = Temp;         // �ҵ��ϴ���ɵĽ�����βָ�롣
                b->next = run;
                delete (b);
                b = NULL;
            }
        }
        else if (ready == tail)
        {
            cout << "��ǰ�������н�ʣ��һ������(" << run->name << ")�ڵ���" << endl;
            cout << "����ִ��ǰ״̬" << endl;
            cout << "----------------------��ǰ�����н���״̬--------------------------" << endl;
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
            cout << setw(8) << run->name << "|" << setw(18) << run->cputime << "|" << setw(10) << run->needtime << "|" << setw(10) << run->prio << "|" << setw(15) << run->state << "|" << endl;
            cout << "����(" << run->name << ")����������" << run->needtime << "��" << endl;
            run->cputime += run->needtime;
            run->needtime = 0;
            run->prio = 50;
            run->state = "R";
            cout << "ִ�����!" << endl;
            cout << setw(8) << run->name << "|" << setw(18) << run->cputime << "|" << setw(10) << run->needtime << "|" << setw(10) << run->prio << "|" << setw(15) << run->state << "|" << endl;
            head->next = run->next;
            run->state = "F";
            run->next = NULL;
            Temp = finish->next;
            while (Temp != NULL)
            {
                Temp = Temp->next;
            }
            PCB *b = Temp; // �ҵ��ϴ���ɵĽ�����βָ�롣
            b->next = run;
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
                cout << "----------------------����ǰ����״̬--------------------------" << endl;
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
                cout << setw(8) << run->name << "|" << setw(18) << run->cputime << "|" << setw(10) << run->needtime << "|" << setw(10) << run->prio << "|" << setw(15) << run->state << "|" << endl;
                run->cputime += run->round;
                run->needtime -= run->round;
                run->prio = 50 - run->needtime;
                run->state = "R";
                cout << "��ǰ���������С�" << endl;
                cout << setw(8) << run->name << "|" << setw(18) << run->cputime << "|" << setw(10) << run->needtime << "|" << setw(10) << run->prio << "|" << setw(15) << run->state << "|" << endl;
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
                cout << "----------------------����ǰ����״̬--------------------------" << endl;
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
                cout << setw(8) << run->name << "|" << setw(18) << run->cputime << "|" << setw(10) << run->needtime << "|" << setw(10) << run->prio << "|" << setw(15) << run->state << "|" << endl;
                cout << setw(8) << run->next->name << "|" << setw(18) << run->next->cputime << "|" << setw(10) << run->next->needtime << "|" << setw(10) << run->next->prio << "|" << setw(15) << run->next->state << "|" << endl;
                run->cputime++;
                run->next->cputime++;
                run->next->state = "R";
                run->needtime--;
                run->next->needtime--;
                run->prio = 50 - run->needtime;
                cout << "��ǰ���������С�" << endl;
                cout << setw(8) << run->name << "|" << setw(18) << run->cputime << "|" << setw(10) << run->needtime << "|" << setw(10) << run->prio << "|" << setw(15) << run->state << "|" << endl;
                cout << setw(8) << run->next->name << "|" << setw(18) << run->next->cputime << "|" << setw(10) << run->next->needtime << "|" << setw(10) << run->next->prio << "|" << setw(15) << run->next->state << "|" << endl;
                // δ��ɵĽ��̷��ؾ������еĶ�β��������һ������
                head->next = run->next->next;
                run->state = "F";
                run->next = NULL;
                finish = run;
                tail->next = run->next;
            }
            else if (finish->state == "R")
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
                Temp = finish;
                while (Temp->next != NULL)
                {
                    Temp = Temp->next;
                }
                PCB *b = Temp; // �ҵ��ϴ���ɵĽ�����βָ�롣
                b->next = run;
                /*
                * delete(Temp);
                * Temp = NULL;
                * Temp = new PCB;
                */
            }
        }
        else if (ready == tail)
        {
            cout << "��ǰ�������н�ʣ��һ������(" << run->name << ")�ڵ���" << endl;
            cout << "����ִ��ǰ״̬" << endl;
            cout << "----------------------��ǰ�����н���״̬--------------------------" << endl;
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
            cout << setw(8) << run->name << "|" << setw(18) << run->cputime << "|" << setw(10) << run->needtime << "|" << setw(10) << run->prio << "|" << setw(15) << run->state << "|" << endl;
            int a = run->needtime % run->round; // �ж��Ƿ�������2
            a = a > 0 ? a + 1 : a;
            cout << "����(" << run->name << ")������ѭ������" << a << "��" << endl;
            run->cputime += run->needtime;
            run->needtime = 0;
            run->prio = 50;
            run->state = "R";
            cout << "ִ�����!" << endl;
            cout << setw(8) << run->name << "|" << setw(18) << run->cputime << "|" << setw(10) << run->needtime << "|" << setw(10) << run->prio << "|" << setw(15) << run->state << "|" << endl;
            head->next = run->next;
            run->state = "F";
            Temp = finish;
            while (Temp->next != NULL)
            {
                Temp = Temp->next;
            }
            PCB *b = Temp; // �ҵ��ϴ���ɵĽ�����βָ�롣
            b->next = run;
            run->next = NULL;
        }
        /*
        * delete(Temp);
        * Temp=NULL;
        * Temp = new PCB;
        */
    }
    /*
    * delete(run);
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
        Temp = head;
        Node = finish;
        while (Temp->next != NULL)
        {
            Temp = Temp->next;
            cout << setw(8) << Temp->name << "|" << setw(18) << Temp->cputime << "|" << setw(10) << Temp->needtime << "|" << setw(10) << Temp->prio << "|" << setw(15) << Temp->state << "|" << endl;
        }
        /*
        * delete(Temp);
        * Temp = NULL;
        * Temp = new PCB;
        */
        if (Node->state != "R")
        {
            while (Node->next != NULL)
            {
                cout << setw(8) << Node->name << "|" << setw(18) << Node->cputime << "|" << setw(10) << Node->needtime << "|" << setw(10) << Node->prio << "|" << setw(15) << Node->state << "|" << endl;
                Node = Node->next;
            }
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
        Temp = head;
        Node = finish;
        while (Temp->next != NULL)
        {
            Temp = Temp->next;
            cout << setw(8) << Temp->name << "|" << setw(18) << Temp->cputime << "|" << setw(10) << Temp->needtime << "|" << setw(10) << Temp->round << "|" << setw(15) << Temp->state << "|" << endl;
        }
        /*
        * delete(Temp);
        * Temp = NULL;
        * Temp = new PCB;
        */
        if (Node->state != "R")
        {
            while (Node->next != NULL)
            {
                cout << setw(8) << Node->name << "|" << setw(18) << Node->cputime << "|" << setw(10) << Node->needtime << "|" << setw(10) << Node->round << "|" << setw(15) << Node->state << "|" << endl;
                Node = Node->next;
            }
        }
    }
    /*
    * delete(Node);
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
    fp->state = "R"; // ��һ���н�����ɻ��û�Ϊ�Ǹ�����
    finish = fp;
    print(pp, fp, 1);
    if (insert1)
    {
        fp = firstin(pp, 1);
        print(pp, fp, 1);
    }
    delete (fp);
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
    fp->state = "R"; // ��һ���н�����ɻ��û�Ϊ�Ǹ�����
    finish = fp;
    print(rp, fp, 2);
    if (insert2)
    {
        fp = firstin(rp, 2);
        print(rp, fp, 2);
    }
    delete (fp);
    fp = NULL;
}

void announce()
{
    int flag;
    cout << "-------------------------------------------------" << endl;
    cout << "---����ϵͳʵ����ʾ---��1805-3��-20183584-������---" << endl;
    cout << "------------ʵ��һ-----���̵���ģ���㷨------------" << endl;
    cout << "-----------------1.�����������㷨-----------------" << endl;
    cout << "-----------------2.ѭ����ת�����㷨---------------" << endl;
    cout << "-----------------3.��ȫ�˳�----------------------" << endl;
    cout << "��ѡ���Ӧ������ţ�";
    cin >> flag;
    switch (flag)
    {
    case 1:
        system("cls");
        cout << "�����������㷨�ɹ�����" << endl;
        prisch();
        break;
    case 2:
        system("cls");
        cout << "ѭ����ת�����㷨�ɹ�����" << endl;
        roundsch();
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
    Node = NULL;
    finish = NULL;
    head = NULL;
    run = NULL;
    Temp = NULL;
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
