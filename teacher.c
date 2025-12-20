#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 最大教师数量
#define MAX_TEACHER 100
// 姓名/工号最大长度
#define MAX_NAME_LEN 20
#define MAX_ID_LEN 10

// 教师信息结构体
typedef struct
{
    // 工号（唯一标识）
    char id[MAX_ID_LEN];
    // 姓名
    char name[MAX_NAME_LEN];
    // 年龄
    int age;
    // 性别（M-男，F-女）
    char gender;
    // 基本工资
    float salary;
    // 奖金
    float bonus;
    // 是否被删除（标记位，避免数组移动）
    int is_deleted;
} Teacher;

// 全局变量：教师数组、当前教师数量
Teacher teachers[MAX_TEACHER];
int teacher_count = 0;

// 函数声明
void menu();
void add_teacher();
void delete_teacher();
void modify_teacher();
void query_teacher();
void show_all_teachers();
int find_teacher_by_id(const char *id);
void clear_input_buffer();

int main()
{
    int choice;
    // 初始化数组（标记所有位置未删除）
    memset(teachers, 0, sizeof(teachers));

    while (1)
    {
        menu();
        printf("请输入操作序号：");
        // 输入校验
        while (scanf("%d", &choice) != 1)
        {
            clear_input_buffer();
            printf("输入无效，请输入数字序号：");
        }
        clear_input_buffer();

        switch (choice)
        {
        case 1:
            add_teacher();
            break;
        case 2:
            delete_teacher();
            break;
        case 3:
            modify_teacher();
            break;
        case 4:
            query_teacher();
            break;
        case 5:
            show_all_teachers();
            break;
        case 0:
            printf("退出系统，感谢使用！\n");
            exit(0);
        default:
            printf("无效序号，请重新输入！\n");
        }
        // 暂停查看结果
        printf("\n按Enter键继续...");
        getchar();
// 清屏（跨平台兼容，Windows用cls，Linux/Mac用clear）
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }
    return 0;
}

// 主菜单
void menu()
{
    printf("========== 教师管理系统 ==========\n");
    printf("1. 添加教师信息\n");
    printf("2. 删除教师信息\n");
    printf("3. 修改教师信息\n");
    printf("4. 查询教师信息\n");
    printf("5. 显示所有教师信息\n");
    printf("0. 退出系统\n");
    printf("==================================\n");
}

// 清空输入缓冲区（解决scanf后getchar读取换行问题）
void clear_input_buffer()
{
    while (getchar() != '\n')
        ;
}

//---------------------------------------------------------------------------------------//
// 根据工号查找教师，返回索引（-1表示未找到）
int find_teacher_by_id(const char *id)
{

}
//---------------------------------------------------------------------------------------//


// 添加教师信息
void add_teacher()
{
    if (teacher_count >= MAX_TEACHER)
    {
        printf("系统容量已满，无法添加新教师！\n");
        return;
    }

    char id[MAX_ID_LEN];
    printf("请输入教师工号：");
    scanf("%s", id);

    // 检查工号是否已存在
    if (find_teacher_by_id(id) != -1)
    {
        printf("该工号已存在，添加失败！\n");
        return;
    }

    // 查找空位置（未被使用或已删除）
    int index = -1;
    for (int i = 0; i < MAX_TEACHER; i++)
    {
        if (teachers[i].is_deleted || teachers[i].id[0] == '\0')
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("系统异常，添加失败！\n");
        return;
    }

    // 填充信息
    Teacher t;
    strcpy(t.id, id);
    printf("请输入教师姓名：");
    scanf("%s", t.name);

    // 年龄输入校验
    printf("请输入教师年龄：");
    while (scanf("%d", &t.age) != 1 || t.age < 18 || t.age > 80)
    {
        clear_input_buffer();
        printf("年龄无效（18-80），请重新输入：");
    }

    // 性别输入校验
    printf("请输入教师性别（M-男，F-女）：");
    while (scanf(" %c", &t.gender) != 1 || (t.gender != 'M' && t.gender != 'F' && t.gender != 'm' && t.gender != 'f'))
    {
        clear_input_buffer();
        printf("性别无效（M/F），请重新输入：");
    }
    // 统一转为大写
    if (t.gender == 'm')
        t.gender = 'M';
    if (t.gender == 'f')
        t.gender = 'F';

    // 工资输入校验
    printf("请输入教师基本工资：");
    while (scanf("%f", &t.salary) != 1 || t.salary < 0)
    {
        clear_input_buffer();
        printf("工资无效（≥0），请重新输入：");
    }

    // 奖金输入校验
    printf("请输入教师奖金：");
    while (scanf("%f", &t.bonus) != 1 || t.bonus < 0)
    {
        clear_input_buffer();
        printf("奖金无效（≥0），请重新输入：");
    }

    t.is_deleted = 0;
    teachers[index] = t;
    teacher_count++;

    printf("教师信息添加成功！\n");
}

//---------------------------------------------------------------------------------------//

// 删除教师信息（逻辑删除，标记is_deleted）
void delete_teacher()
{
char id[MAX_ID_LEN];
	printf("请输入要删除的教师工号：");
	scanf("%s",id);
	int index = find_teacher_by_id(id);
	if(index == -1)
	{
		printf("未找到该教师，删除失败！\n");
		return ;
	}
	teachers[index].is_deleted = 1;
	teacher_count--;
	printf("教师信息删除成功！\n");
}

//---------------------------------------------------------------------------------------//

// 修改教师信息
void modify_teacher()
{
    char id[MAX_ID_LEN];
    printf("请输入要修改的教师工号：");
    scanf("%s", id);

    int index = find_teacher_by_id(id);
    if (index == -1)
    {
        printf("未找到该教师，修改失败！\n");
        return;
    }

    Teacher *t = &teachers[index];
    printf("当前信息：\n");
    printf("姓名：%s，年龄：%d，性别：%c，基本工资：%.2f，奖金：%.2f\n",
           t->name, t->age, t->gender, t->salary, t->bonus);

    printf("请输入新姓名（回车保持不变）：");
    char new_name[MAX_NAME_LEN];
    // 读取整行（支持空输入）
    fgets(new_name, MAX_NAME_LEN, stdin);
    // 去掉换行符
    new_name[strcspn(new_name, "\n")] = '\0';
    if (strlen(new_name) > 0)
    {
        strcpy(t->name, new_name);
    }

    // 修改年龄
    printf("请输入新年龄（回车保持不变，18-80）：");
    char age_str[10];
    fgets(age_str, 10, stdin);
    age_str[strcspn(age_str, "\n")] = '\0';
    if (strlen(age_str) > 0)
    {
        int new_age = atoi(age_str);
        if (new_age >= 18 && new_age <= 80)
        {
            t->age = new_age;
        }
        else
        {
            printf("年龄无效，保持原数值！\n");
        }
    }

    // 修改性别
    printf("请输入新性别（M/F，回车保持不变）：");
    char gender_str[2];
    fgets(gender_str, 2, stdin);
    gender_str[strcspn(gender_str, "\n")] = '\0';
    if (strlen(gender_str) > 0)
    {
        char new_gender = gender_str[0];
        if (new_gender == 'M' || new_gender == 'F' || new_gender == 'm' || new_gender == 'f')
        {
            if (new_gender == 'm')
                new_gender = 'M';
            if (new_gender == 'f')
                new_gender = 'F';
            t->gender = new_gender;
        }
        else
        {
            printf("性别无效，保持原数值！\n");
        }
    }

    // 修改工资
    printf("请输入新基本工资（回车保持不变，≥0）：");
    char salary_str[20];
    fgets(salary_str, 20, stdin);
    salary_str[strcspn(salary_str, "\n")] = '\0';
    if (strlen(salary_str) > 0)
    {
        float new_salary = atof(salary_str);
        if (new_salary >= 0)
        {
            t->salary = new_salary;
        }
        else
        {
            printf("工资无效，保持原数值！\n");
        }
    }

    // 修改奖金
    printf("请输入新奖金（回车保持不变，≥0）：");
    char bonus_str[20];
    fgets(bonus_str, 20, stdin);
    bonus_str[strcspn(bonus_str, "\n")] = '\0';
    if (strlen(bonus_str) > 0)
    {
        float new_bonus = atof(bonus_str);
        if (new_bonus >= 0)
        {
            t->bonus = new_bonus;
        }
        else
        {
            printf("奖金无效，保持原数值！\n");
        }
    }

    printf("教师信息修改成功！\n");
}

// 查询教师信息（按工号（完成更改版））
void query_teacher()
{
    char id[MAX_ID_LEN];
    printf("请输入要查询的教师工号：");
    scanf("%s",id);
    int index=find_teacher_by_id(id);
    if(index==-1)
    {
        printf("未找到该工号的教师！\n");
    }
    Teacher *t=&teacher[index];
    printf("\n********** 教师信息 **********\n");
    printf("工号: %s\n",t->id);
    printf("姓名: %s\n",t->name);
    printf("年龄: %s\n",t->age);
    printf("性别: %s\n",t->gender=="M"?"男":"女");
    printf("基础工资: %.2f 元\n",t->salary);
    printf("奖金: %.2f 元\n",t->bonus);
    printf("总薪资: %.2f 元\n",t->salary + t->bonus);
    printf("*******************************\n");
}


//---------------------------------------------------------------------------------------//
// 显示所有教师信息
void show_all_teachers()
{
    if (teacher_count == 0)
    {
        printf("暂无教师信息！\n");
        return;
    }
    printf("********** 所有教师信息 **********\n");
    printf("工号\t姓名\t年龄\t性别\t基本工资\t奖金\t总薪资\n");
    printf("-----------------------------------\n");
    for (int i = 0; i < MAX_TEACHERS; i++)
    {
        if (!teachers[i].is_deleted && teachers[i].id[0] != '\0')
        {
            Teacher t = teachers[i];
            printf("%s\t%s\t%d\t%s\t%.2f\t\t%.2f\t%.2f\n",
                   t.id, t.name, t.age,
                   t.gender == 'M' ? "男" : "女",
                   t.salary, t.bonus, t.salary + t.bonus);
        }
    }
    printf("**********************************\n");
}
//---------------------------------------------------------------------------------------//
