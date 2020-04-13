#include "head.h"
#include "eightnumber.h"
#include "ui_eightnumber.h"
extern int terminated_matrix[Matrix_size][Matrix_size];


//初始化八数码问题状态
ItemPtr eightNumber::init_problem(){
    int i=0,j=0,mark=1,signal[9]={0};//signal数组用于记录初始化情况
    ItemPtr head=(ItemPtr)malloc(sizeof(item));
    if(head!=NULL){
        mark=0;
        for(i=0;i<9;i++){
            signal[i]=0;
        }
        //scanf data from ui
        head->matrix[0][0]=ui->init_1->text().toInt();
        head->matrix[0][1]=ui->init_2->text().toInt();
        head->matrix[0][2]=ui->init_3->text().toInt();
        head->matrix[1][0]=ui->init_4->text().toInt();
        head->matrix[1][1]=ui->init_5->text().toInt();
        head->matrix[1][2]=ui->init_6->text().toInt();
        head->matrix[2][0]=ui->init_7->text().toInt();
        head->matrix[2][1]=ui->init_8->text().toInt();
        head->matrix[2][2]=ui->init_9->text().toInt();
        //check data validation
        for(int i=0;i<Matrix_size;i++){
            for(int j=0;j<Matrix_size;j++){
                signal[head->matrix[i][j]]=1;//0-8数字必须都输入且不能有重复
            }
        }
        for(int i=0;i<9;i++){
            if(!signal[i]){
                mark=1;//用于判断初始状态正确性的变量
            }
        }
        if(mark){
            QMessageBox::information(NULL,"Warning","Initial State Error!",QMessageBox::Yes,QMessageBox::Yes);
            return NULL;
        }
        head->g_x=0;
        head->h_x=count_h(head);
        head->f_x=head->g_x+head->h_x;//原理公式
        head->next=NULL;
        head->pre=NULL;
    }
}
//初始化open表
DListPtr eightNumber::init_DList()
{
   DListPtr plist=(DListPtr)malloc(sizeof(DList));
   ItemPtr head=init_problem();
   if(plist!=NULL){
       if(head!=NULL){
           plist->head=head;
           plist->tail=head;
       }
       else{//无初始状态
           free(plist);
           return NULL;
       }
   }
   else{
       printf("Fail to malloc DList\n");
       exit(0);
   }
   return plist;
}
//初始化close表
DListPtr eightNumber::init_Close()
{
  DListPtr close=(DListPtr)malloc(sizeof(DList));
  if(close!=NULL){
      close->head=NULL;
      close->tail=NULL;
  }
  else{
      printf("Fail to malloc DList\n");
      exit(0);
  }
  return close;
}
//比较两节点
//相同返回0，不同返回1
int eightNumber::compare_two_node(ItemPtr first,ItemPtr second)
{
    int i=0,j=0;
    for(i=0;i<Matrix_size;i++){
        for(j=0;j<Matrix_size;j++){
            if(first->matrix[i][j]!=second->matrix[i][j]){
                return 1;
            }
        }
    }
    return 0;//两节点相同
}
//检查输入输出有效性
//有效返回1，无效返回0
int eightNumber::check_valid(DListPtr list)
{
    int sum1=0,sum2=0;
    int signal[9]={0},arr1[9]={0},arr2[9]={0};
    int mark=0;
    int i=0,j=0;
    for(i=0;i<Matrix_size;i++){
        for(j=0;j<Matrix_size;j++){
            arr1[i*3+j]=terminated_matrix[i][j];//3*i+j对应数字顺序
            arr2[i*3+j]=list->head->matrix[i][j];
        }
    }
    for(i=0;i<9;i++){
        for(j=0;j<i;j++){
            if(arr1[i]&&arr1[i]<arr1[j]){
                sum1++;
            }
            if(arr2[i]&&arr2[i]<arr2[j]){
                sum2++;
            }
        }
    }
    //check the validation of terminated data
    for(i=0;i<Matrix_size;i++){
        for(j=0;j<Matrix_size;j++){
            signal[terminated_matrix[i][j]]++;
        }
    }
    for(i=0;i<9;i++){
        if(!signal[i]||signal[i]>1){//有数字重复出现或1-8有数字未出现
            mark++;
        }
    }
    if(mark>1){//mark留个1代表0
        QMessageBox::information(NULL,"Warning","Final State Error!",QMessageBox::Yes,QMessageBox::Yes);
        return -1;
    }
    if((sum1%2)==(sum2%2)){
        return 1;
    }
    return 0;
}
//程序处理入口
ItemPtr eightNumber::deal()
{
    int end=1;
    ItemPtr first=NULL;
    while(end&&open->head!=NULL){
        first=get_open_first(open);
        if(check(first)){
            end=0;//找到目标结点
            break;
        }
        add_close(close,first);
        expand(open,close,first);
        first=NULL;
    }
    if(end){
        QMessageBox::critical(this,"No Solution","Why there is no result?",QMessageBox::Yes,QMessageBox::Yes);
        return NULL;
    }
    return first;
}
//释放open或lose表
void eightNumber::free_list(DListPtr list)
{
    ItemPtr node=NULL;
    if(list!=NULL){
        while(list->head!=NULL){
            node=list->head;
            list->head=list->head->next;
            free(node);
            node=NULL;
        }
        free(list);
        list=NULL;
    }
}
//取open表的第一个节点
ItemPtr eightNumber::get_open_first(DListPtr open)
{
    ItemPtr first=NULL;
    first=open->head;
    if(open->head==open->tail){//open表中当前只剩一个结点
        open->head=NULL;
        open->tail=NULL;
    }
    else{
        open->head=open->head->next;//open表第一个节点下移
    }
    return first;
}
//遍历close表检查这个状态是否已经出现过
//走过返回1，没走过返回0
int eightNumber::search_close(DListPtr close,ItemPtr new_node)
{
    ItemPtr node=NULL;
    if(close->head==NULL){//当前close表为空
        return 0;
    }
    else{
        node=close->head;
        while(node!=NULL){
            if(!compare_two_node(node,new_node)){//相同节点
                if(node->g_x>new_node->g_x){
                    node->g_x=new_node->g_x;
                    node->f_x=new_node->f_x;
                    node->pre=new_node->pre;
                }
                break;
            }
            node=node->next;
        }
    }
    if(node==NULL){//完成全部遍历
        return 0;

    }
    else{
        return 1;
    }
}

//找到0所在的格子
int eightNumber::find_0(ItemPtr node)
{
    int i=0,j=0,result=0;
    for(i=0;i<Matrix_size;i++){
        for(j=0;j<Matrix_size;j++){
            if(node->matrix[i][j]==0){
                result=(i+1)*10+j;
            }
        }
    }
    return result;
}
//将节点加入open表中
void eightNumber::add_open(DListPtr open,ItemPtr node)
{
    ItemPtr ptr=NULL,prePtr=NULL;
    if(open->head==NULL){//当前open表为空
        open->head=node;
        open->tail=node;
    }
    else{
        ptr=open->head;
        while(ptr!=NULL&&ptr->f_x<=node->f_x){//f_x是评估节点重要性的估价函数
            //需要选择估价函数值f_x最小的节点进行扩展
            prePtr=ptr;
            ptr=ptr->next;
        }
        if(ptr==NULL){
            open->tail->next=node;//f_x最大，放在open表的最尾端
            open->tail=node;
        }
        else{//不在最尾端，完成当前插入
            if(prePtr==NULL){//应插入最首部
                node->next=open->head;
                open->head=node;
            }
            else{
                prePtr->next=node;
                node->next=ptr;//ptr就是原prePtr->next
            }
        }
    }
    ptr=NULL;
    prePtr=NULL;//处理指针
}
//将扩展节点加入close表，该节点扩展成功
void eightNumber::add_close(DListPtr close,ItemPtr node)
{
    if(close->head==NULL){//close表为空
        close->head=node;
        close->tail=node;
    }
    else{
        node->next=NULL;
        close->tail->next=node;
        close->tail=node;
    }
}
//用1、2、3、4代替上、下、左、右进行扩展后的填充
void eightNumber::step(int x,int y,int mark,ItemPtr node,DListPtr open,DListPtr close)
{
    ItemPtr new_node=NULL;
    int i=0,j=0;
    new_node=(ItemPtr)malloc(sizeof(item));
    if(new_node){
        for(i=0;i<Matrix_size;i++){
            for(j=0;j<Matrix_size;j++){
                new_node->matrix[i][j]=node->matrix[i][j];
            }
        }
        switch(mark){
        case 1:
            new_node->matrix[x][y]=new_node->matrix[x+1][y];
            new_node->matrix[x+1][y]=0;
            break;
        case 2:
            new_node->matrix[x][y]=new_node->matrix[x-1][y];
            new_node->matrix[x-1][y]=0;
            break;
        case 3:
            new_node->matrix[x][y]=new_node->matrix[x][y+1];
            new_node->matrix[x][y+1]=0;
            break;
        case 4:
            new_node->matrix[x][y]=new_node->matrix[x][y-1];
            new_node->matrix[x][y-1]=0;
            break;
        }
        new_node->g_x=node->g_x+1;//表示进入下一层
        new_node->pre=node;//指明拓展流程
        new_node->next=NULL;
        new_node->h_x=count_h(new_node);
        new_node->f_x=new_node->g_x+new_node->h_x;
        if(!search_close(close,new_node)){//没走过
            add_open(open,new_node);//加入open表
            new_node=NULL;
        }
        else{//走过
            free(new_node);
            new_node=NULL;

        }
    }
    else{
        printf("cannot malloc new_node\n");
        exit(0);
    }
}
//根据空格（0）所在位置进行拓展试探，进行判重
void eightNumber::give_try(int x,int y,ItemPtr node,DListPtr open,DListPtr close)
{
    int count=0;
    if(x==1&&y==0){
        count=0;
        while(++count<5){
            switch(count){
            case 1:
            {
                step(x,y,1,node,open,close);
                break;
            }
            case 2:
            {
                step(x,y,2,node,open,close);
                break;
            }
            case 3:
            {
                step(x,y,3,node,open,close);
                break;
            }
            case 4:
            {
                step(x,y,4,node,open,close);
                break;
            }
            default:
                break;
            }
        }
    }
    else if(x == 1 && y == 0) {        //[1][0]    上下左
        count = 0;
        while (++count < 4) {
            switch (count) {
                case 1:
                {
                    step(x, y, 1, node, open, close);
                    break;
                }
                case 2:
                {
                    step(x, y, 2, node, open, close);
                    break;
                }
                case 3:
                {
                    step(x, y, 3, node, open, close);
                    break;
                }
                default:
                    break;
            }
        }
    }
    else if (x == 1 && y == 2) {        //[1][2]    上下右
        count = 0;
        while (++count < 4) {
            switch (count) {
                case 1:
                {
                    step(x, y, 1, node, open, close);
                    break;
                }
                case 2:
                {
                    step(x, y, 2, node, open, close);
                    break;
                }
                case 3:
                {
                    step(x, y, 4, node, open, close);
                    break;
                }
                default:
                    break;
            }
        }
    }
    else if (x == 0 && y == 1) {        //[0][1]    上左右
        count = 0;
        while (++count < 4) {
            switch (count) {
                case 1:
                {
                    step(x, y, 1, node, open, close);
                    break;
                }
                case 2:
                {
                    step(x, y, 3, node, open, close);
                    break;
                }
                case 3:
                {
                    step(x, y, 4, node, open, close);
                    break;
                }
                default:
                    break;
            }
        }
    }
    else if (x == 2 && y == 1) {        //[2][1]    下左右
        count = 0;
        while (++count < 4) {
            switch (count) {
                case 1:
                {
                    step(x, y, 2, node, open, close);
                    break;
                }
                case 2:
                {
                    step(x, y, 3, node, open, close);
                    break;
                }
                case 3:
                {
                    step(x, y, 4, node, open, close);
                    break;
                }
                default:
                    break;
            }
        }
    }
    else if (x == 0 && y == 0) {        //[0][0]    上左
        count = 0;
        while (++count < 3) {
            switch (count) {
                case 1:
                {
                    step(x, y, 1, node, open, close);
                    break;
                }
                case 2:
                {
                    step(x, y, 3, node, open, close);
                    break;
                }
                default:
                    break;
            }
        }
    }
    else if (x == 0 && y == 2) {        //[0][2]    左下
        count = 0;
        while (++count < 3) {
            switch (count) {
                case 1:
                {
                    step(x, y, 2, node, open, close);
                    break;
                }
                case 2:
                {
                    step(x, y, 3, node, open, close);
                    break;
                }
                default:
                    break;
            }
        }
    }
    else if (x == 2 && y == 0) {        //[2][0]    下左
        count = 0;
        while (++count < 3) {
            switch (count) {
                case 1:
                {
                    step(x, y, 2, node, open, close);
                    break;
                }
                case 2:
                {
                    step(x, y, 3, node, open, close);
                    break;
                }
                default:
                    break;
            }
        }
    }
    else {                              //[2][2]    下右
        count = 0;
        while (++count < 3) {
            switch (count) {
                case 1:
                {
                    step(x, y, 2, node, open, close);
                    break;
                }
                case 2:
                {
                    step(x, y, 4, node, open, close);
                    break;
                }
                default:
                    break;
            }
        }
    }
}
//拓展该节点的下一个状态
void eightNumber::expand(DListPtr open,DListPtr close,ItemPtr cur_node)
{
    int position=0,position_x=0,position_y=0;
    position=find_0(cur_node);
    position_x=position/10-1;
    position_y=position%10;
    give_try(position_x,position_y,cur_node,open,close);
}
//检查当前open表的第一个节点是否为目标结点
//1是目标结点，0则不是
int eightNumber::check(ItemPtr node)
{
    int i=0,j=0;
    for(i=0;i<Matrix_size;i++){
        for(j=0;j<Matrix_size;j++){
            if(node->matrix[i][j]!=terminated_matrix[i][j]){
                return 0;
            }
        }
    }
    return 1;
}
//输出全部处理过程
int eightNumber::process_output(ItemPtr node)
{
    if(node!=NULL){
        int i=process_output(node->pre);
        if(i==0){
            ui->show1->setText(QString::number(node->matrix[0][0]));
            ui->show2->setText(QString::number(node->matrix[0][1]));
            ui->show3->setText(QString::number(node->matrix[0][2]));
            ui->show4->setText(QString::number(node->matrix[1][0]));
            ui->show5->setText(QString::number(node->matrix[1][1]));
            ui->show6->setText(QString::number(node->matrix[1][2]));
            ui->show7->setText(QString::number(node->matrix[2][0]));
            ui->show8->setText(QString::number(node->matrix[2][1]));
            ui->show9->setText(QString::number(node->matrix[2][2]));
            int result=find_0(node);
            find_label(result)->setText("");//是0的位置不显示
            return result;
        }
        else{
            int temp=find_0(node);
            int row=i/10-1;
            int col=i%10;
            int a=node->matrix[row][col];
            QLabel* label_i=find_label(i);
            QLabel* label_temp=find_label(temp);

            QElapsedTimer t;
            t.start();
            while(t.elapsed()<1000)
                QCoreApplication::processEvents();
            label_i->setText(QString::number(a));
            label_temp->setText("");

            return temp;
        }
    }
    else{//initial state
        return 0;
    }
}
//找到所在标签位
QLabel * eightNumber::find_label(int i)
{
    int a=i/10-1;
    int b=i%10;
    switch(a*3+b+1){
    case 1:
        return ui->show1;
        break;
    case 2:
        return ui->show2;
        break;
    case 3:
        return ui->show3;
        break;
    case 4:
        return ui->show4;
        break;
    case 5:
        return ui->show5;
        break;
    case 6:
        return ui->show6;
        break;
    case 7:
        return ui->show7;
        break;
    case 8:
        return ui->show8;
        break;
    case 9:
        return ui->show9;
        break;
    }
}
