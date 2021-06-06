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
// 将指针初始化为NULL?
PCB *create(int, int); // 用于创建进程（头插法）

bool insert1(PCB *); // 优先数调度就绪队列排序

bool insert2(PCB *); // 时间片轮转调度就绪队列排序

PCB *firstin(PCB *, int); // 调度就绪队列第一个进程投入运行

void print(PCB *, PCB *, int); // 每次运行进程后打印进程状态

void prisch(); // 优先数调度算法

void roundsch(); // 时间片轮转调度算法

void announce(); // 系统顶层样式

void clearAllP(); //  清空指针

PCB *create(int n, int r)
{
    /*
    * head = new PCB;
    * Node = new PCB;
    */
    head->next = NULL; // 初始化头结点
    if (n > 0)
    {
        cout << "准备创建" << n << "进程" << endl;
        string pname;
        int time;
        for (int counter = 1; counter < n + 1; counter++)
        {
            // 头插法创建进程链表
            cout << "正在创建第" << counter << "个进程" << endl;
            cout << "键入进程名称(string)：";
            cin >> pname;
            cout << "键入进程需要时间(int)：";
            cin >> time;
            Node->name = pname;
            Node->needtime = time;
            //Node->cputime = 0;
            Node->next = head->next;
            Node->prio = 50 - Node->needtime;
            Node->round = r; // 两个时间片为一个单位
            //Node->state = "W";
            head->next = Node;
        }
    }
    else // 判断输入的整型是否为正数
    {
        cout << "创建数非法，请重试！" << endl;
        int nn = 0;
        cout << "请输入正确的创建数：";
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
                // 将值向后传。
                PCB *tp = new PCB; // 临时PCB指针
                tp->cputime = Temp->cputime;
                tp->name = Temp->name;
                tp->needtime = Temp->needtime;
                tp->next = Temp->next;
                tp->prio = Temp->prio;
                tp->round = Temp->round;
                tp->state = Temp->state;
                Temp = Temp->next;
                Temp->next = tp;
                delete (tp); // 清除临时指针
                tp = NULL;   // 置空指针
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
        cout << "就绪队列已无进程" << endl;
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
            PCB *p = head->next; // 临时指针
            head->next = p->next;
            p->next = NULL;
            tail->next = p;
            ready = head->next;
            tail = p;
            delete (p); // 去除临时指针
            p = NULL;   // 置空指针
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
        cout << "就绪队列没有进程了" << endl;
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
                cout << "当前投入运行的进程为：" << run->name << endl;
                cout << "调度执行前状态" << endl;
                cout << "----------------------运行前进程状态--------------------------" << endl;
                cout << setw(8) << "进程名"
                     << "|" << setw(18) << "已占用CPU时间片数"
                     << "|" << setw(10) << "剩余时间"
                     << "|" << setw(10) << "当前优先数"
                     << "|" << setw(15) << "当前进程状态"
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
                cout << "当前进程运行中。" << endl;
                cout << setw(8) << run->name << "|" << setw(18) << run->cputime << "|" << setw(10) << run->needtime << "|" << setw(10) << run->prio << "|" << setw(15) << run->state << "|" << endl;
                // 未完成的进程返回就绪队列的队尾，进行下一次排序
                head->next = run->next;
                run->state = "W";
                run->next = NULL;
                tail->next = run;
                /*
                * PCB* b = new PCB;// 临时指针
                * b = Temp;// 设置就绪队列尾指针
                * b->next = run;
                * delete(b);// 清除临时指针
                * b = NULL;// 置空指针
                */
            }
            else if (finish->state == "R") // 判断是否有进程已经完成，只有第一次有进程完成时才满足两个条件
            {
                head->next = run->next;
                run->state = "F";
                run->next = NULL;
                finish = run;
            }
            else
            {
                // 尾插法在finish后插入后续完成的进程
                head->next = run->next;
                run->state = "F";
                run->next = NULL;
                Temp = finish->next;
                while (Temp != NULL)
                {
                    Temp = Temp->next;
                }
                PCB *b = new PCB; // 临时指针
                b = Temp;         // 找到上次完成的进程做尾指针。
                b->next = run;
                delete (b);
                b = NULL;
            }
        }
        else if (ready == tail)
        {
            cout << "当前就绪队列仅剩余一个进程(" << run->name << ")在调度" << endl;
            cout << "调度执行前状态" << endl;
            cout << "----------------------当前待运行进程状态--------------------------" << endl;
            cout << setw(8) << "进程名"
                 << "|" << setw(18) << "已占用CPU时间片数"
                 << "|" << setw(10) << "剩余时间"
                 << "|" << setw(10) << "当前优先数"
                 << "|" << setw(15) << "当前进程状态"
                 << "|" << endl;
            cout << setw(8) << "name"
                 << "|" << setw(18) << "cputime"
                 << "|" << setw(10) << "needtime"
                 << "|" << setw(10) << "priority"
                 << "|" << setw(15) << "state"
                 << "|" << endl;
            cout << setw(8) << run->name << "|" << setw(18) << run->cputime << "|" << setw(10) << run->needtime << "|" << setw(10) << run->prio << "|" << setw(15) << run->state << "|" << endl;
            cout << "进程(" << run->name << ")即将被调度" << run->needtime << "次" << endl;
            run->cputime += run->needtime;
            run->needtime = 0;
            run->prio = 50;
            run->state = "R";
            cout << "执行完毕!" << endl;
            cout << setw(8) << run->name << "|" << setw(18) << run->cputime << "|" << setw(10) << run->needtime << "|" << setw(10) << run->prio << "|" << setw(15) << run->state << "|" << endl;
            head->next = run->next;
            run->state = "F";
            run->next = NULL;
            Temp = finish->next;
            while (Temp != NULL)
            {
                Temp = Temp->next;
            }
            PCB *b = Temp; // 找到上次完成的进程做尾指针。
            b->next = run;
        }
    }
    else
    {
        if (ready != tail)
        {
            if (run->needtime > 1) // 最小单位有两个时间片，小于1时，可以让下一个进程投入调度
            {
                cout << "当前投入运行的进程为：" << run->name << endl;
                cout << "调度执行前状态" << endl;
                cout << "----------------------运行前进程状态--------------------------" << endl;
                cout << setw(8) << "进程名"
                     << "|" << setw(18) << "已占用CPU时间片数"
                     << "|" << setw(10) << "剩余时间"
                     << "|" << setw(10) << "当前优先数"
                     << "|" << setw(15) << "当前进程状态"
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
                cout << "当前进程运行中。" << endl;
                cout << setw(8) << run->name << "|" << setw(18) << run->cputime << "|" << setw(10) << run->needtime << "|" << setw(10) << run->prio << "|" << setw(15) << run->state << "|" << endl;
                // 未完成的进程返回就绪队列的队尾，进行下一次排序
                head->next = run->next;
                run->state = "W";
                run->next = NULL;
                tail->next = run;
            }
            else if (run->needtime == 1 && finish->state == "R")
            {
                cout << "当前投入运行的进程为：" << run->name << "和" << run->next->name << endl;
                cout << "调度执行前状态" << endl;
                cout << "----------------------运行前进程状态--------------------------" << endl;
                cout << setw(8) << "进程名"
                     << "|" << setw(18) << "已占用CPU时间片数"
                     << "|" << setw(10) << "剩余时间"
                     << "|" << setw(10) << "当前优先数"
                     << "|" << setw(15) << "当前进程状态"
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
                cout << "当前进程运行中。" << endl;
                cout << setw(8) << run->name << "|" << setw(18) << run->cputime << "|" << setw(10) << run->needtime << "|" << setw(10) << run->prio << "|" << setw(15) << run->state << "|" << endl;
                cout << setw(8) << run->next->name << "|" << setw(18) << run->next->cputime << "|" << setw(10) << run->next->needtime << "|" << setw(10) << run->next->prio << "|" << setw(15) << run->next->state << "|" << endl;
                // 未完成的进程返回就绪队列的队尾，进行下一次排序
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
                // 尾插法在finish后插入后续完成的进程
                head->next = run->next;
                run->state = "F";
                run->next = NULL;
                Temp = finish;
                while (Temp->next != NULL)
                {
                    Temp = Temp->next;
                }
                PCB *b = Temp; // 找到上次完成的进程做尾指针。
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
            cout << "当前就绪队列仅剩余一个进程(" << run->name << ")在调度" << endl;
            cout << "调度执行前状态" << endl;
            cout << "----------------------当前待运行进程状态--------------------------" << endl;
            cout << setw(8) << "进程名"
                 << "|" << setw(18) << "已占用CPU时间片数"
                 << "|" << setw(10) << "剩余时间"
                 << "|" << setw(10) << "当前优先数"
                 << "|" << setw(15) << "当前进程状态"
                 << "|" << endl;
            cout << setw(8) << "name"
                 << "|" << setw(18) << "cputime"
                 << "|" << setw(10) << "needtime"
                 << "|" << setw(10) << "priority"
                 << "|" << setw(15) << "state"
                 << "|" << endl;
            cout << setw(8) << run->name << "|" << setw(18) << run->cputime << "|" << setw(10) << run->needtime << "|" << setw(10) << run->prio << "|" << setw(15) << run->state << "|" << endl;
            int a = run->needtime % run->round; // 判断是否能整除2
            a = a > 0 ? a + 1 : a;
            cout << "进程(" << run->name << ")即将被循环调度" << a << "次" << endl;
            run->cputime += run->needtime;
            run->needtime = 0;
            run->prio = 50;
            run->state = "R";
            cout << "执行完毕!" << endl;
            cout << setw(8) << run->name << "|" << setw(18) << run->cputime << "|" << setw(10) << run->needtime << "|" << setw(10) << run->prio << "|" << setw(15) << run->state << "|" << endl;
            head->next = run->next;
            run->state = "F";
            Temp = finish;
            while (Temp->next != NULL)
            {
                Temp = Temp->next;
            }
            PCB *b = Temp; // 找到上次完成的进程做尾指针。
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
        cout << "--------------------------进程状态表------------------------------" << endl;
        cout << setw(8) << "进程名"
             << "|" << setw(18) << "已占用CPU时间片数"
             << "|" << setw(10) << "剩余时间"
             << "|" << setw(10) << "当前优先数"
             << "|" << setw(15) << "当前进程状态"
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
        cout << "--------------------------进程状态表------------------------------" << endl;
        cout << setw(8) << "进程名"
             << "|" << setw(18) << "已占用CPU时间片数"
             << "|" << setw(10) << "剩余时间"
             << "|" << setw(10) << "时间片"
             << "|" << setw(15) << "当前进程状态"
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
    cout << "请输入创建进程个数：";
    cin >> pn;
    PCB *pp = create(pn, 2);
    PCB *fp = new PCB; // 临时完成指针
    fp->next = NULL;
    fp->state = "R"; // 第一次有进程完成会置换为那个进程
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
    * cout << "是否要更换时间片数：" << "(y/n)";
    * cin >> choose;
    * if (choose == 'y' || choose == 'Y')
    * {
        //时间片数，对应print也要变化
    * } */
    cout << "设置最小单位时间片数：";
    cin >> rr;
    int rn;
    cout << "请输入创建进程个数：";
    cin >> rn;
    PCB *rp = create(rn, rr);
    PCB *fp = new PCB; // 临时完成指针
    fp->next = NULL;
    fp->state = "R"; // 第一次有进程完成会置换为那个进程
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
    cout << "---操作系统实验演示---信1805-3班-20183584-刘瑞阳---" << endl;
    cout << "------------实验一-----进程调度模拟算法------------" << endl;
    cout << "-----------------1.优先数调度算法-----------------" << endl;
    cout << "-----------------2.循环轮转调度算法---------------" << endl;
    cout << "-----------------3.安全退出----------------------" << endl;
    cout << "请选择对应操作序号：";
    cin >> flag;
    switch (flag)
    {
    case 1:
        system("cls");
        cout << "优先数调度算法成功启动" << endl;
        prisch();
        break;
    case 2:
        system("cls");
        cout << "循环轮转调度算法成功启动" << endl;
        roundsch();
        break;
    case 3:
        cout << "系统已安全退出" << endl;
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
    cout << "指针已全部置空" << endl;
}

int main()
{
    announce();
    clearAllP();
    system("pause");
    return 0;
}
