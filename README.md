# lr0
lr(0)分析法的实现（应该）
这个是进行学校的编译原理实验时候写的，简单的文法应该是没有问题的。有一个对移进-归约冲突、归约-归约冲突的判断。实现了自动生成closure集，构表，分析输入串等功能
为了方便将输入串固定了，所以输入输入串的部分可能需要修改(init()部分)

都是拓广文法后

测试的文法：

S->P
P->m,r
P->m,i
P->r,r
P->r,i
P->r,m

S->E
E->BB
B->aB
B->b

(有冲突)
S->E
E->E+T
E->T
T->T*F
T->F
F->(E)
F->i
