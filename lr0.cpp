#include<iostream>
#include<map>
#include<fstream>
#include<string>
#include<stack>
using namespace std;
#define wherenum 100
string Action[50][50];
string Goto[50][50];
map<int, pair<string, string>>chanshengshi;//产生式,左部与右部
map<pair<string, string>, int>wherechanshengshi;
pair<pair<string,string>, int>xiangmuchanshengshi;//项目的产生式以及点所在的位置
map<int, pair<pair<string,string>, int>>xiangmu;//项目以及对应的编号
int num_chanshengshi, num_vt, num_vn, num_xiangmu,num_closure;//产生式终结符非终结符项目闭包个数
map<string, int>vt;
map<string, int>vn;
map<int, string>wherevt;
map<int, string>wherevn;
 struct closure{
	int num=NULL;//闭包的编号
	string first;//第一行的项目
	int all[50];//全部项目,项目对应的编号
	int count = -1;//项目个数
	int spot=-1;//第一个项目的"."所在位置
	int father[50];//父代
	string fatherpoint[10];
	string nextpoint[10];
	int fathercount = -1;//父代跳转到当前状态的个数
	string x[50];//经什么跳转
	int next[50];//每一个项目，点后移跳转到的闭包位置
	int scount = -1;//已经连接到子代的个数
}theclosure[20];
void setchanshengshi()
{
	fstream f;
	f.open("test1.txt",ios::in);
	f >> num_vt;
	cout << "终结符个数" << num_vt << endl<<"终结符:";
	for (int i = 0; i < num_vt; i++)
	{
		string str;
		f >> str;
		vt.insert(pair<string, int>(str, i));
		wherevt.insert(pair<int, string>(i, str));
		cout << str;
	}
	vt.insert(pair<string, int>("#", num_vt));
	wherevt.insert(pair<int, string>(num_vt, "#"));
	num_vt++;
	f >> num_vn;
	cout << "非终结符个数" << num_vn << endl << "非终结符:";
	for (int i = 0; i < num_vn; i++)
	{
		string str;
		f >> str;
		vn.insert(pair<string, int>(str, i));
		wherevn.insert(pair<int, string>(i, str));
		cout << str;
	}
	cout << "产生式个数";
	f >> num_chanshengshi;
	cout << num_chanshengshi;
	cout << "输入拓广后的文法，S为文法开始符" << endl;
	for (int i = 0; i < num_chanshengshi; i++)
	{
		string l, r;
		f >> l;
		f >> r;
		cout << l << "->" << r << endl;
		chanshengshi.insert(pair<int, pair<string, string>>(i, pair<string, string>(l, r)));
		wherechanshengshi.insert(pair<pair<string, string>, int>(pair<string, string>(l, r), i));
	}
}
void judge()
{
	for (int i = 0; i < num_chanshengshi; i++)
	{
		pair<string, string>chansheng = chanshengshi[i];
		string right = chansheng.second;
		for (int x = 0; x < num_chanshengshi; x++)
		{
			string part = chanshengshi[x].second.substr(0, right.length());
			string allright = chanshengshi[x].second;
			if (x!=i)
			{
				if (right == part)cout << chansheng.first << "->" << chansheng.second <<"\t"<<chanshengshi[x].first<<"->"<<chanshengshi[x].second<< "移入-归约冲突" << endl;
			}
			if (x!=i)
			{
				if(chansheng.second==chanshengshi[x].second)cout << chansheng.first << "->" << chansheng.second << "\t" << chanshengshi[x].first << "->" << chanshengshi[x].second << "归约-归约冲突" << endl;
			}
			if (x!=i)
			{
				string apart = "";
				if (chanshengshi[x].second.length() > right.length()) {
					apart = chanshengshi[x].second.substr(chanshengshi[x].second.length() - right.length(), chanshengshi[x].second.length());
				}
				if(apart==right)cout << chansheng.first << "->" << chansheng.second << "\t" << chanshengshi[x].first << "->" << chanshengshi[x].second << "归约-归约冲突" << endl;
			}
		}
	}
}
void createproject()
{
	num_xiangmu = 0;
	for (int i = 0; i < num_chanshengshi; i++)
	{
		string str = chanshengshi[i].second;
		for (int z = 0; z <=str.length(); z++)
		{
			xiangmu.insert(pair<int, pair<pair<string, string>, int>>(num_xiangmu,pair<pair<string, string>,int>(pair<string,string>(chanshengshi[i].first,chanshengshi[i].second),z)));
			num_xiangmu++;
		}
	}
	for (int i = 0; i < num_xiangmu; i++)
	{
		string str=xiangmu[i].first.second;
		string str1 = str.insert(xiangmu[i].second, ".");
		cout << "项目"<<xiangmu[i].first.first << "->" << str1<<"\t.在右部第"<<xiangmu[i].second<<"位"<<"\t右部长度为"<< xiangmu[i].first.second.length()<<endl;
	}
}
int searchsame(int x)//项目的编号
{
	//for (int i = 0; i < num_xiangmu; i++)
	//{
	//	for (int a = 0; a <= num_closure; a++)
	//	{

	//		if (xiangmu[i].first.first == xiangmu[theclosure[a].all[0]].first.first&&i != theclosure[a].all[0] && xiangmu[i].second == theclosure[a].spot)
	//		{
	//			string s = xiangmu[i].first.second;
	//			char buf[100];
	//			strcpy(buf, s.c_str());
	//			string next;
	//			for (int x = 0; x <= xiangmu[i].second; x++)
	//			{
	//				next.push_back(buf[x]);
	//			}
	//			string st = xiangmu[theclosure[a].all[0]].first.second;
	//			char ch[100];
	//			strcpy(ch, st.c_str());
	//			string nex;
	//			for (int x = 0; x <= theclosure[a].spot; x++)
	//			{
	//				nex.push_back(ch[x]);
	//			}
	//			cout << (nex == next);
	//			if (nex == next)return a;
	//		}
	//	}
	//}
	return -1;
}
int search(int x)//项目位置，但项目在多个集合中都可能有，只能看存不存在
{
	if (num_closure < 0)return -1;
	for (int i = 0; i <= num_closure; i++)
	{
		/*for (int a = 0; a <= theclosure[i].count;  a++)
		{
			if (x == theclosure[i].all[a])return i;
		}*/
		if (x ==theclosure[i].all[0])return i;//都是找第一个，因为第一个是获得一个字符推导过来的，其他的是由空字推导的
	}
	return -1;
}
int searchexist(int x)//是否存在
{
	if (num_closure < 0)return -1;
	for (int i = 0; i <= num_closure; i++)
	{
		for (int a = 0; a <= theclosure[i].count;  a++)
		{
			if (x == theclosure[i].all[a])return i;
		}
		//if (x == theclosure[i].all[0])return i;//都是找第一个，因为第一个是获得一个字符推导过来的，其他的是由空字推导的
	}
	return -1;
}
void dfs(int closurenum, string s)
{
	for (int i = 0; i < num_xiangmu; i++)
	{
		if (xiangmu[i].second == 0 && xiangmu[i].first.first == s)
		{
			int flag = 1;
			for (int z = 0; z <= theclosure[closurenum].count; z++)//与closure中的比较，防止重复
			{
				if (theclosure[closurenum].all[z] == i)flag = 0;
			}
				/*if (searchsameth(i) == closurenum)*/ 
			if(flag==1){
					theclosure[closurenum].count++;
					theclosure[closurenum].all[theclosure[closurenum].count] = i;
					string a = xiangmu[i].first.second;
					char ch[100];
					strcpy(ch, a.c_str());
					string n;
					n.push_back(ch[0]);
					if (vn.count(n) == 1)
					{
						dfs(closurenum, n);
					}
				}
		}
	}
}
int searchson()
{
	for (int i = 0; i <= num_closure; i++)
	{
		if (theclosure[i].first.length() == theclosure[i].spot) { continue; }//遇到归约项目跳过
		if (theclosure[i].count != theclosure[i].scount)return 1;//如果仍存在状态中项目与下一个状态不对应的情况
	}
	return 0;
}
int searchsameth(int x,int now)//用点已经后移的项目进行搜寻
{
	if (search(x) == -1)//找不到
	{
		/*pair<string,string>*/
		pair<pair<string, string>, int>str = xiangmu[x];
		str.second++;
		/*int z = -1;
		for (int i = 0; i < num_xiangmu; i++)
		{
			if (str == xiangmu[i])z = i;
		}
		if (z == -1)return -1;*/
		for (int i = 0; i <= num_closure; i++)//寻找closure
		{
			for (int z = 0; z <= theclosure[i].count; z++)//遍历closure里的项目
			{
				if (theclosure[i].all[z] != x)//不存在该项目
				{
					if (xiangmu[theclosure[i].all[z]].first.first == xiangmu[x].first.first)//左部相同
					{
						if (xiangmu[theclosure[i].all[z]].second == xiangmu[x].second)//点的位置相同
						{
							string s = xiangmu[theclosure[i].all[z]].first.second;
							string st = xiangmu[x].first.second;
							char ch[100];
							char buf[100];
							strcpy(ch, s.c_str());
							strcpy(buf, st.c_str());
							string n;
							string ne;
							//int b = -1;
							for (int h = 0; h < xiangmu[x].second; h++)//获取前缀
							{
								n.push_back(ch[h]);
								ne.push_back(buf[h]);
								/*cout << n << "\t" << ne << "\t" << endl;
								cout << i<<endl;*/
							}
							if (n == ne) {//前缀相同
								/*if (theclosure[i].father[z] == now)*/ { /*cout << "\t"<<"there" << endl;*/ return i; }//来源于同一个父代，相当于一起接收字符，.一起后移，前缀相同
							}//不需要来源于同一父代
						}
					}
				}
			}
		}
	}
	/*cout << "help"<<endl;*/
	return -1;
}
void createclosure()
{//从文法开始符开始
	int now=0;//进行中的closure,当前状态
	int position = 0;//项目在map中的位置
	pair<pair<string, string>, int>str = xiangmu[0];
	num_closure = 0;
	theclosure[0].num = 0;
	theclosure[0].first = str.first.first + str.first.second;
	theclosure[0].count++;
	theclosure[0].all[theclosure[0].count] = 0;
	theclosure[0].spot = str.second;
	//获取.后面的第一位
	string s = str.first.second;
	char buf[100];
	strcpy(buf, s.c_str());
	string next;
	next.push_back(buf[str.second]);
	//cout << "a" << next << "a" << endl;
	//cout << next<<endl<<buf[0]<<vn.count(next);
	if (vn.count(next)==1) {
		//如果.的下一位是非终结符,则搜索项目，将.的位置为0的存入closure中
		dfs(0, next);
	}
	//
	int c = 0;
	while (theclosure[0].scount != theclosure[0].count)//从文法开始符开始
	{
		theclosure[0].scount++;
		pair<pair<string, string>, int>str1 = xiangmu[theclosure[0].all[theclosure[0].scount]];
		int i = str1.second + 1;//点后移，相当于输入了一个字符
		for (int x = 0; x < num_xiangmu; x++)//遍历项目
		{
			if (str1.first == xiangmu[x].first && i == (xiangmu[x].second))//找到了所需项目的编号
			{
				
				int z = search(x);//寻找项目集是否有项目
				int exist = searchexist(x);//判断是否存在一个项目不在项目集的第一行
				if (exist != -1)z = exist;
				if (z == -1)//找不到
				{
					int a = searchsameth(x,now);//寻找是否有项目的前缀相同的项目，来源于同一个closure集
					if (a==-1) {//创建新的closure集
						num_closure++;//
						int n = num_closure;
						theclosure[n].num = n;
						theclosure[n].count++;//项目数增加
						theclosure[n].first = xiangmu[x].first.first + xiangmu[x].first.second;
						theclosure[n].all[theclosure[n].count] = x;
						theclosure[n].spot = xiangmu[x].second;
						theclosure[n].fathercount++;
						theclosure[n].father[theclosure[n].fathercount] = 0;//获得父代位置，但父代可能有多个
						//theclosure[now].scount++;
						theclosure[now].next[theclosure[now].scount] = n;//扫描一个字符后指向的下一个closure集
						string strin = xiangmu[theclosure[now].all[theclosure[now].scount]].first.second;
						char cha[100];
						strcpy(cha, strin.c_str());
						string nt;
						nt.push_back(cha[xiangmu[theclosure[now].all[theclosure[now].scount]].second]);
						theclosure[now].nextpoint[theclosure[now].scount] = nt;//经过边到达子代
						string st = xiangmu[x].first.second;
						char ch[100];
						strcpy(ch, st.c_str());
						string ne;
						ne.push_back(ch[xiangmu[x].second]);//压入空的字符，证明到末尾了，就没有dfs了
						//cout << "a" << ch[xiangmu[x].second] << "a" << endl;
						theclosure[n].fatherpoint[theclosure[n].fathercount] = ne;
						if (vn.count(ne) == 1)dfs(n, ne);//求经过空字的项目
					}
					else {
						theclosure[a].count++;//存在一个项目集，前缀相同
						theclosure[a].all[theclosure[a].count] = x;
						theclosure[a].fathercount++;
						theclosure[a].father[theclosure[a].fathercount] = now;//父节点没必要
						string strin = xiangmu[theclosure[now].all[theclosure[now].scount]].first.second;//产生式左部
						char cha[100];
						strcpy(cha, strin.c_str());
						string nt;
						nt.push_back(cha[xiangmu[theclosure[now].all[theclosure[now].scount]].second]);
						theclosure[now].nextpoint[theclosure[now].scount] = nt;
						theclosure[now].next[theclosure[now].scount] = a;//当前项目集得到新的项目集的位置
						string st = xiangmu[x].first.second;
						char ch[100];
						strcpy(ch, st.c_str());
						string ne;
						ne.push_back(ch[xiangmu[x].second]);//判断点后的带扫描字符是不是非终结符
						theclosure[a].fatherpoint[theclosure[a].fathercount] = ne;
						if (vn.count(ne) == 1)dfs(a, ne);//是的话用dfs
					}
				}
				else {//不能做到father与本项目一一对应
					//theclosure[z].count++;
					//theclosure[z].all[theclosure[z].count] = x;
					theclosure[z].fathercount++;//找到项目集
					theclosure[z].father[theclosure[z].fathercount] = now;
					string st = xiangmu[x].first.second;
					char ch[100];
					strcpy(ch, st.c_str());
					string ne;
					ne.push_back(ch[xiangmu[x].second]);
					theclosure[z].fatherpoint[theclosure[z].fathercount] = ne;
					//theclosure[now].scount++;
					theclosure[now].next[theclosure[now].scount] = z;//将当前项目集的next指向找到的项目集
					string strin = xiangmu[theclosure[now].all[theclosure[now].scount]].first.second;
					char cha[100];
					strcpy(cha, strin.c_str());
					string nt;
					nt.push_back(cha[xiangmu[theclosure[now].all[theclosure[now].scount]].second]);
					theclosure[now].nextpoint[theclosure[now].scount] = nt;//储存带扫描字符串的第一个字符下一个字符到达下一个项目集
					/*string st = xiangmu[x].first.second;
					char ch[100];
					strcpy(ch, st.c_str());
					string nex;
					nex.push_back(ch[xiangmu[x].second]);
					if (vn.count(nex) == 1)dfs(z, nex);*/
				}
			}
		}
	}
	int flag = 1;
	while (now != num_closure||flag==1)
	{
		flag = searchson();//寻找还没有对应关系的项目集中的项目
		/*string st = xiangmu[theclosure[now].all[0]].first.second;
		char ch[100];
		strcpy(ch, st.c_str());
		string ne;
		ne.push_back(ch[theclosure[now].spot]);
		if (vn.count(ne) == 1)dfs(now, ne);*/
		//now++;
		for (int m = 0; m <= num_closure; m++)//遍历每个closure集
		{
			now = m;//当前项目
			while (theclosure[now].scount != theclosure[now].count)//
			{
				theclosure[now].scount++;//不管有没有对应的，都是要增加，所以不用担心由于归约项目导致的死循环
				pair<pair<string, string>, int>str1 = xiangmu[theclosure[now].all[theclosure[now].scount]];//没有子代的项目
				int i = str1.second+1;//点后移一位 +1行，不+1不行，如果是规约项目，后移之后寻找后对应的是一个不存在的集合
				for (int x = 0; x < num_xiangmu; x++)//遍历项目集，找相同的项目集
				{
					if (str1.first == xiangmu[x].first && i == (xiangmu[x].second))//不存在的话跳过，虽然没有，但是子代scount还是增加的
					{
						int z = search(x);//找项目集
						int exist = searchexist(x);//判断是否存在一个项目不在项目集的第一行
						if (exist != -1)z = exist;
						if (z == -1)//找不到
						{
							int a = searchsameth(x,now);//找到前缀相同的项目的项目集
							if (a == -1)//找不到
							{
								num_closure++;//项目集数量增加
								int n = num_closure;
								theclosure[n].num = n;//赋值
								theclosure[n].count++;
								theclosure[n].first = xiangmu[x].first.first + xiangmu[x].first.second;
								theclosure[n].all[theclosure[n].count] = x;
								theclosure[n].spot = xiangmu[x].second;
								theclosure[n].fathercount++;
								theclosure[n].father[theclosure[n].fathercount] = now;
								//theclosure[now].scount++;
								theclosure[now].next[theclosure[now].scount] = n;
								string strin = xiangmu[theclosure[now].all[theclosure[now].scount]].first.second;
								char cha[100];
								strcpy(cha, strin.c_str());
								string nt;
								nt.push_back(cha[xiangmu[theclosure[now].all[theclosure[now].scount]].second]);
								theclosure[now].nextpoint[theclosure[now].scount] = nt;
								string stri = xiangmu[x].first.second;
								char ch[100];
								strcpy(ch, stri.c_str());
								string nex;
								nex.push_back(ch[xiangmu[x].second]);
								theclosure[n].fatherpoint[theclosure[n].fathercount] = nex;
								if (vn.count(nex) == 1)dfs(n, nex);//如果
							}
							else {
								//int a = searchsameth(x);
								theclosure[a].count++;
								theclosure[a].all[theclosure[a].count] = x;
								theclosure[a].fathercount++;
								theclosure[a].father[theclosure[a].fathercount] = now;
								theclosure[now].next[theclosure[now].scount] = a;
								string strin = xiangmu[theclosure[now].all[theclosure[now].scount]].first.second;
								char cha[100];
								strcpy(cha, strin.c_str());
								string nt;
								nt.push_back(cha[xiangmu[theclosure[now].all[theclosure[now].scount]].second]);
								theclosure[now].nextpoint[theclosure[now].scount] = nt;
								string stri = xiangmu[x].first.second;
								char ch[100];
								strcpy(ch, stri.c_str());
								string nex;
								nex.push_back(ch[xiangmu[x].second]);
								theclosure[a].fatherpoint[theclosure[a].fathercount] = nex;
								if (vn.count(nex) == 1)dfs(a, nex);
							}
						}
						else {
							//theclosure[z].count++;
							//theclosure[z].all[theclosure[z].count] = x;
							theclosure[z].fathercount++;
							theclosure[z].father[theclosure[z].fathercount] = now;
							//theclosure[now].scount++;
							string stri = xiangmu[x].first.second;
							char ch[100];
							strcpy(ch, stri.c_str());
							string nex;
							nex.push_back(ch[xiangmu[x].second]);
							theclosure[z].fatherpoint[theclosure[z].fathercount] = nex;
							theclosure[now].next[theclosure[now].scount] = z;
							string strin = xiangmu[theclosure[now].all[theclosure[now].scount]].first.second;
							char cha[100];
							strcpy(cha, strin.c_str());
							string nt;
							nt.push_back(cha[xiangmu[theclosure[now].all[theclosure[now].scount]].second]);
							theclosure[now].fatherpoint[theclosure[now].scount] = nt;
							/*string stri = xiangmu[x].first.second;
							char ch[100];
							strcpy(ch, stri.c_str());
							string nex;
							nex.push_back(ch[xiangmu[x].second]);
							if (vn.count(nex) == 1)dfs(z, nex);*/
						}
					}
				}
			}
		}
	}
	for (int i = 0; i <=num_closure; i++)//输出项目集
	{
		cout << "I" << i << endl;
		for (int x = 0; x <= theclosure[i].count; x++)
		{
			cout<<xiangmu[theclosure[i].all[x]].first.first << "->" << xiangmu[theclosure[i].all[x]].first.second <<"\t.在"<< xiangmu[theclosure[i].all[x]].second <<"\t"<<theclosure[i].next[x]<<"\t"<< theclosure[i].nextpoint[x] <<"\t"<< endl;
		}
		cout << endl;
	}
}
int GO(int x,string n)//项目集编号，符号
{
	for (int i = 0; i < theclosure[x].scount; i++)
	{
		if (theclosure[x].nextpoint[i] == n)
		{
			return theclosure[x].next[i];
		}
	}
	return -1;
}
int Go(int x, string n)
{
	string stri = "";
	for (int i = 0; i <= theclosure[x].count; i++)
	{
		int y = theclosure[x].all[i];
		pair < pair<string, string>, int >str = xiangmu[y];
		char ch[100];
		string st = str.first.second;
		strcpy(ch, st.c_str());
		string next;
		next.push_back(ch[str.second]);//提取经过的字符
		if (next == n) {
			str.second++;
			for (int z = 0; z < num_xiangmu; z++)
			{
				if (str == xiangmu[z])
				{

					return search(z);
				}
			}
		}
	}
	return -1;
}
int gogo(int x, string n)//项目集编号，输入字符
{//可以直接通过nextpoint 以及next来确定下一个项目集，但为了安全，先进行验证
	string stri = "";
	for (int i = 0; i <= theclosure[x].count; i++)//遍历项目集中的项目
	{
		int y = theclosure[x].all[i];
		pair < pair<string, string>, int >str = xiangmu[y];
		char ch[100];
		string st = str.first.second;
		strcpy(ch, st.c_str());
		string next;
		next.push_back(ch[str.second]);//提取待扫描符号串的第一个符号
		if (next == n) {//找到对应的输入，对应的项目
			str.second++;//点后移，获取项目
			for (int z = 0; z < num_xiangmu; z++)//遍历项目
			{
				if (str == xiangmu[z])//找到对应的项目，如果是归约项目的话，点后移，就会找不到项目了
				{//找z
					if (theclosure[x].next[i] != NULL) {//项目获取一个字符到下一个项目集
						int a = theclosure[x].next[i];
						for (int b = 0; b <= theclosure[a].count; b++)//遍历next项目集的项目
						{
							if (theclosure[a].all[b] == z)return a;//存在点后移后的项目，证明该项目集就是需要的集合的编号
						}
					}
					//return search(z);
				}
			}
		}
	}
	return -1;
}
int GoGo(int x, string n)
{
	for (int i = 0; i <= theclosure[x].scount; i++)
	{
		if (theclosure[x].nextpoint[i] == n)return theclosure[x].next[i];
	}
	return -1;
}
void createActionGoto()
{
	/*for (int i = 0; i < num_xiangmu; i++)*/
	for (int z = 0; z <= num_closure; z++)//每个集合中的每个项目进行一次构表，相同的会覆盖
	{
		for (int f = 0; f <= theclosure[z].count;f++)
		{
			int i = theclosure[z].all[f];
			if (xiangmu[i].first.second.length() == xiangmu[i].second)//归约项目
			{
				//cout << "a" << endl;
				if (i == 1) {//acc，接受项目一般在固定位置
					int x = search(i);
					Action[x][vt["#"]] = "acc";
				}
				else {//r
					int x = search(i);
					/*cout << x << endl;
					cout << xiangmu[i].first.first << "->" << xiangmu[i].first.second << "点在" << xiangmu[i].second << endl;*/
					pair<string, string>str = xiangmu[i].first;
					int n = wherechanshengshi[str];//产生式位置
					for (int h = 0; h < num_vt; h++)
					{
						Action[x][h] = "r" + to_string(n);//r+存放产生式位置
					}
				}
			}
			else {
				//int x = search(i);
				//cout << z << endl;
				//cout << xiangmu[i].first.first << "->" << xiangmu[i].first.second << "点在" << xiangmu[i].second << endl;
				char ch[100];
				string str = xiangmu[i].first.second;
				strcpy(ch, str.c_str());
				string next;
				next.push_back(ch[xiangmu[i].second]);//获取点后的字符，代表获取的输入
				//cout << "\"" << next << "\"" << endl;
				if (vn.count(next) == 1)//非终结符，待约项目
				{
					int y = GoGo(z, next);//存在项目集
					//cout << "->" << y << "<-" << endl;
					if (y != -1)Goto[z][vn[next]] = to_string(y);
				}
				if (vt.count(next) == 1)//终结符，移进项目
				{
					int y = GoGo(z, next);//存在项目集
					//cout << "<->" << y << "<->" << endl;
					if (y != -1)Action[z][vt[next]] = "s" + to_string(y);
				}
			}
		}
	}
}
void showtable()
{
	for (int i = 0; i < num_vt; i++)
	{
		cout <<"\t"<< wherevt[i];
	}
	for (int i = 1; i < num_vn; i++)
	{
		cout  << "\t"<< wherevn[i];
	}
	cout << endl;
	for (int i = 0; i <= num_closure; i++)
	{
		cout << i << "\t";
		for (int x = 0; x < num_vt; x++)
		{
			cout << Action[i][x] << "\t";
		}
		for (int x = 1; x < num_vn; x++)
		{
			cout << Goto[i][x] << "\t";
		}
		cout << endl;
	}
	//for (int i = 0; i < num_vt; i++)
	//{
	//	cout << "\t" << wherevt[i];
	//}
	//cout << endl;
	//for (int i = 0; i <= num_closure; i++)
	//{
	//	cout << i << "\t";
	//	for (int x = 0; x < num_vt; x++)
	//	{
	//		cout << Action[i][x] << "\t";
	//	}
	//	cout << endl;
	//}
	//for (int i = 0; i < num_vn; i++)
	//{
	//	cout << wherevn[i] << "\t";
	//}
	//cout << endl;
	//for (int i = 0; i < num_closure; i++)
	//{
	//	for (int x = 0; x < num_vn; x++)
	//	{
	//		if (!(Goto[i][x].empty()))
	//			cout << i << ',' << Goto[i][x] << "\t";
	//		else {

	//			cout << "\t";
	//		}
	//	}

	//	cout << endl;
	//}
}
string code;
char chcode[10];
string strcode[wherenum];
int b;
void init()
{
	cout << "输入串，包括#" ;
	//cin >> code;
	code = "i+i*i";
	cout << "请输入要分析的输入串的字符个数(不包括#)："<<endl;
	cin >> b;
	b = b + 1;
	string input;
	cout << "请输入要分析的输入串(#为结尾）:";
	for(int h=0;h<b;h++)
	{
		cin>>strcode[h];
	}
	for (int i = 0; i < b; i++)
	{
		cout << strcode[i];
	}
	cout << endl;
}
stack<string>ch;
stack<int>status;
void showstackch()
{
	stack<string>n = ch;
	for (int i = 0; i < ch.size(); i++)
	{
		cout << n.top();
		n.pop();
	}
	cout << "\t";
}
void showstackstatus()
{
	stack<int>n = status;
	for (int i = 0; i < ch.size(); i++)
	{
		cout << n.top();
		n.pop();
	}
	cout << "\t";
}
void analyse()
{
	ch.push("#");
	status.push(0);
	int n = 0;//输入串指向位置
	cout << endl;
	while (1)
	{
		showstackch();
		showstackstatus();
		int x = status.top();
		string z = Action[x][vt[strcode[n]]];//读action表
		string temp = z.substr(0, 1);//获取字符串中的第一个字符，判断是r，s
		string num;
		for (int j = n; j < b; j++)//输出输入串
		{
			cout << strcode[j];
		}
		cout << "\t";
		if(z.length()>1)num = z.substr(1);//获取数字
		if (temp == "s")//移进
		{
			cout << num << "入栈" << endl;
			status.push(atoi(num.c_str()));//状态入栈
			ch.push(strcode[n]);//输入字符入栈
			n++;//下一个字符
		}
		else if (temp == "r")//归约
		{
			int n = atoi(num.c_str());//转换为数字
			cout << "用" << chanshengshi[n].first << "->" << chanshengshi[n].second << "归约"<<endl;
			for (int i = 0; i < chanshengshi[n].second.length(); i++)
			{
				status.pop();//出栈
				ch.pop();//出栈
			}
			ch.push(chanshengshi[n].first);//符号入栈
			string g = Goto[status.top()][vn[ch.top()]];//获取goto表的状态
			int j = atoi(g.c_str());
			status.push(j);//状态入栈
		}
		else if (z == "acc")
		{
			cout << "分析成功" << endl;
			break;
		}
		else {
			cout << temp << num << endl;
			cout << "error" << endl;
			break;
		}
		cout << endl;
		/*int x = status.top();
		string z;
		z.push_back(chcode[n]);
		string temp = Action[x][vt[z]];
		char buf[10];
		strcpy(buf, temp.c_str());
		string next;
		next.push_back(buf[0]);
		int n = 0;
		for (int i = 1; i < 10; i++)
		{
		}
		if (buf[0] == 's')
		{
			ch.push(chcode[n]);
			status.push(buf[1] - '0');
		}
		if (buf[0] == 'r')
		{
			int x = buf[1] - '0';
			pair<string, string>houxuanshi = chanshengshi[x];
			for (int i = 0; i < houxuanshi.second.length(); i++)
			{
				status.pop();
				ch.pop();
			}
			string t = houxuanshi.first;
			char bu[10];
			strcpy(bu, t.c_str());
			string ne;
			ne.push_back(buf[0]);
			ch.push(bu[0]);
			if (Goto[status.top()][vn[ne]].size()!=0)
			{
				string nex = Goto[status.top()][vn[ne]];
				int h=atoi(nex.c_str());
				status.push(h);
			}
			else {
				cout << "error" << endl;
				break;
			}
		}
		if (temp == "acc")
		{
			cout << "成功" << endl;
			break;
		}
		else {
			cout << "error" << endl;
			break;
		}*/
	}
}
void showDFA()
{
	//for (int i = 0; i <= num_closure; i++)
	//{
	//	cout << "I" << i << endl;
	//	for (int x = 0; x < theclosure[i].scount; x++)
	//	{
	//		cout << theclosure[i].nextpoint[theclosure[i].scount] << "\t" << theclosure[i].next[theclosure[i].scount] << endl;
	//	}
	//}
}
int main()
{
	setchanshengshi();
	judge();
	createproject();
	createclosure();
	createActionGoto();
	showtable();
	init();
	analyse();
	system("pause");
}