#include<iostream>
#include<map>
#include<fstream>
#include<string>
#include<stack>
using namespace std;
#define wherenum 100
string Action[50][50];
string Goto[50][50];
map<int, pair<string, string>>chanshengshi;//����ʽ,�����Ҳ�
map<pair<string, string>, int>wherechanshengshi;
pair<pair<string,string>, int>xiangmuchanshengshi;//��Ŀ�Ĳ���ʽ�Լ������ڵ�λ��
map<int, pair<pair<string,string>, int>>xiangmu;//��Ŀ�Լ���Ӧ�ı��
int num_chanshengshi, num_vt, num_vn, num_xiangmu,num_closure;//����ʽ�ս�����ս����Ŀ�հ�����
map<string, int>vt;
map<string, int>vn;
map<int, string>wherevt;
map<int, string>wherevn;
 struct closure{
	int num=NULL;//�հ��ı��
	string first;//��һ�е���Ŀ
	int all[50];//ȫ����Ŀ,��Ŀ��Ӧ�ı��
	int count = -1;//��Ŀ����
	int spot=-1;//��һ����Ŀ��"."����λ��
	int father[50];//����
	string fatherpoint[10];
	string nextpoint[10];
	int fathercount = -1;//������ת����ǰ״̬�ĸ���
	string x[50];//��ʲô��ת
	int next[50];//ÿһ����Ŀ���������ת���ıհ�λ��
	int scount = -1;//�Ѿ����ӵ��Ӵ��ĸ���
}theclosure[20];
void setchanshengshi()
{
	fstream f;
	f.open("test1.txt",ios::in);
	f >> num_vt;
	cout << "�ս������" << num_vt << endl<<"�ս��:";
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
	cout << "���ս������" << num_vn << endl << "���ս��:";
	for (int i = 0; i < num_vn; i++)
	{
		string str;
		f >> str;
		vn.insert(pair<string, int>(str, i));
		wherevn.insert(pair<int, string>(i, str));
		cout << str;
	}
	cout << "����ʽ����";
	f >> num_chanshengshi;
	cout << num_chanshengshi;
	cout << "�����ع����ķ���SΪ�ķ���ʼ��" << endl;
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
				if (right == part)cout << chansheng.first << "->" << chansheng.second <<"\t"<<chanshengshi[x].first<<"->"<<chanshengshi[x].second<< "����-��Լ��ͻ" << endl;
			}
			if (x!=i)
			{
				if(chansheng.second==chanshengshi[x].second)cout << chansheng.first << "->" << chansheng.second << "\t" << chanshengshi[x].first << "->" << chanshengshi[x].second << "��Լ-��Լ��ͻ" << endl;
			}
			if (x!=i)
			{
				string apart = "";
				if (chanshengshi[x].second.length() > right.length()) {
					apart = chanshengshi[x].second.substr(chanshengshi[x].second.length() - right.length(), chanshengshi[x].second.length());
				}
				if(apart==right)cout << chansheng.first << "->" << chansheng.second << "\t" << chanshengshi[x].first << "->" << chanshengshi[x].second << "��Լ-��Լ��ͻ" << endl;
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
		cout << "��Ŀ"<<xiangmu[i].first.first << "->" << str1<<"\t.���Ҳ���"<<xiangmu[i].second<<"λ"<<"\t�Ҳ�����Ϊ"<< xiangmu[i].first.second.length()<<endl;
	}
}
int searchsame(int x)//��Ŀ�ı��
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
int search(int x)//��Ŀλ�ã�����Ŀ�ڶ�������ж������У�ֻ�ܿ��治����
{
	if (num_closure < 0)return -1;
	for (int i = 0; i <= num_closure; i++)
	{
		/*for (int a = 0; a <= theclosure[i].count;  a++)
		{
			if (x == theclosure[i].all[a])return i;
		}*/
		if (x ==theclosure[i].all[0])return i;//�����ҵ�һ������Ϊ��һ���ǻ��һ���ַ��Ƶ������ģ����������ɿ����Ƶ���
	}
	return -1;
}
int searchexist(int x)//�Ƿ����
{
	if (num_closure < 0)return -1;
	for (int i = 0; i <= num_closure; i++)
	{
		for (int a = 0; a <= theclosure[i].count;  a++)
		{
			if (x == theclosure[i].all[a])return i;
		}
		//if (x == theclosure[i].all[0])return i;//�����ҵ�һ������Ϊ��һ���ǻ��һ���ַ��Ƶ������ģ����������ɿ����Ƶ���
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
			for (int z = 0; z <= theclosure[closurenum].count; z++)//��closure�еıȽϣ���ֹ�ظ�
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
		if (theclosure[i].first.length() == theclosure[i].spot) { continue; }//������Լ��Ŀ����
		if (theclosure[i].count != theclosure[i].scount)return 1;//����Դ���״̬����Ŀ����һ��״̬����Ӧ�����
	}
	return 0;
}
int searchsameth(int x,int now)//�õ��Ѿ����Ƶ���Ŀ������Ѱ
{
	if (search(x) == -1)//�Ҳ���
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
		for (int i = 0; i <= num_closure; i++)//Ѱ��closure
		{
			for (int z = 0; z <= theclosure[i].count; z++)//����closure�����Ŀ
			{
				if (theclosure[i].all[z] != x)//�����ڸ���Ŀ
				{
					if (xiangmu[theclosure[i].all[z]].first.first == xiangmu[x].first.first)//����ͬ
					{
						if (xiangmu[theclosure[i].all[z]].second == xiangmu[x].second)//���λ����ͬ
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
							for (int h = 0; h < xiangmu[x].second; h++)//��ȡǰ׺
							{
								n.push_back(ch[h]);
								ne.push_back(buf[h]);
								/*cout << n << "\t" << ne << "\t" << endl;
								cout << i<<endl;*/
							}
							if (n == ne) {//ǰ׺��ͬ
								/*if (theclosure[i].father[z] == now)*/ { /*cout << "\t"<<"there" << endl;*/ return i; }//��Դ��ͬһ���������൱��һ������ַ���.һ����ƣ�ǰ׺��ͬ
							}//����Ҫ��Դ��ͬһ����
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
{//���ķ���ʼ����ʼ
	int now=0;//�����е�closure,��ǰ״̬
	int position = 0;//��Ŀ��map�е�λ��
	pair<pair<string, string>, int>str = xiangmu[0];
	num_closure = 0;
	theclosure[0].num = 0;
	theclosure[0].first = str.first.first + str.first.second;
	theclosure[0].count++;
	theclosure[0].all[theclosure[0].count] = 0;
	theclosure[0].spot = str.second;
	//��ȡ.����ĵ�һλ
	string s = str.first.second;
	char buf[100];
	strcpy(buf, s.c_str());
	string next;
	next.push_back(buf[str.second]);
	//cout << "a" << next << "a" << endl;
	//cout << next<<endl<<buf[0]<<vn.count(next);
	if (vn.count(next)==1) {
		//���.����һλ�Ƿ��ս��,��������Ŀ����.��λ��Ϊ0�Ĵ���closure��
		dfs(0, next);
	}
	//
	int c = 0;
	while (theclosure[0].scount != theclosure[0].count)//���ķ���ʼ����ʼ
	{
		theclosure[0].scount++;
		pair<pair<string, string>, int>str1 = xiangmu[theclosure[0].all[theclosure[0].scount]];
		int i = str1.second + 1;//����ƣ��൱��������һ���ַ�
		for (int x = 0; x < num_xiangmu; x++)//������Ŀ
		{
			if (str1.first == xiangmu[x].first && i == (xiangmu[x].second))//�ҵ���������Ŀ�ı��
			{
				
				int z = search(x);//Ѱ����Ŀ���Ƿ�����Ŀ
				int exist = searchexist(x);//�ж��Ƿ����һ����Ŀ������Ŀ���ĵ�һ��
				if (exist != -1)z = exist;
				if (z == -1)//�Ҳ���
				{
					int a = searchsameth(x,now);//Ѱ���Ƿ�����Ŀ��ǰ׺��ͬ����Ŀ����Դ��ͬһ��closure��
					if (a==-1) {//�����µ�closure��
						num_closure++;//
						int n = num_closure;
						theclosure[n].num = n;
						theclosure[n].count++;//��Ŀ������
						theclosure[n].first = xiangmu[x].first.first + xiangmu[x].first.second;
						theclosure[n].all[theclosure[n].count] = x;
						theclosure[n].spot = xiangmu[x].second;
						theclosure[n].fathercount++;
						theclosure[n].father[theclosure[n].fathercount] = 0;//��ø���λ�ã������������ж��
						//theclosure[now].scount++;
						theclosure[now].next[theclosure[now].scount] = n;//ɨ��һ���ַ���ָ�����һ��closure��
						string strin = xiangmu[theclosure[now].all[theclosure[now].scount]].first.second;
						char cha[100];
						strcpy(cha, strin.c_str());
						string nt;
						nt.push_back(cha[xiangmu[theclosure[now].all[theclosure[now].scount]].second]);
						theclosure[now].nextpoint[theclosure[now].scount] = nt;//�����ߵ����Ӵ�
						string st = xiangmu[x].first.second;
						char ch[100];
						strcpy(ch, st.c_str());
						string ne;
						ne.push_back(ch[xiangmu[x].second]);//ѹ��յ��ַ���֤����ĩβ�ˣ���û��dfs��
						//cout << "a" << ch[xiangmu[x].second] << "a" << endl;
						theclosure[n].fatherpoint[theclosure[n].fathercount] = ne;
						if (vn.count(ne) == 1)dfs(n, ne);//�󾭹����ֵ���Ŀ
					}
					else {
						theclosure[a].count++;//����һ����Ŀ����ǰ׺��ͬ
						theclosure[a].all[theclosure[a].count] = x;
						theclosure[a].fathercount++;
						theclosure[a].father[theclosure[a].fathercount] = now;//���ڵ�û��Ҫ
						string strin = xiangmu[theclosure[now].all[theclosure[now].scount]].first.second;//����ʽ��
						char cha[100];
						strcpy(cha, strin.c_str());
						string nt;
						nt.push_back(cha[xiangmu[theclosure[now].all[theclosure[now].scount]].second]);
						theclosure[now].nextpoint[theclosure[now].scount] = nt;
						theclosure[now].next[theclosure[now].scount] = a;//��ǰ��Ŀ���õ��µ���Ŀ����λ��
						string st = xiangmu[x].first.second;
						char ch[100];
						strcpy(ch, st.c_str());
						string ne;
						ne.push_back(ch[xiangmu[x].second]);//�жϵ��Ĵ�ɨ���ַ��ǲ��Ƿ��ս��
						theclosure[a].fatherpoint[theclosure[a].fathercount] = ne;
						if (vn.count(ne) == 1)dfs(a, ne);//�ǵĻ���dfs
					}
				}
				else {//��������father�뱾��Ŀһһ��Ӧ
					//theclosure[z].count++;
					//theclosure[z].all[theclosure[z].count] = x;
					theclosure[z].fathercount++;//�ҵ���Ŀ��
					theclosure[z].father[theclosure[z].fathercount] = now;
					string st = xiangmu[x].first.second;
					char ch[100];
					strcpy(ch, st.c_str());
					string ne;
					ne.push_back(ch[xiangmu[x].second]);
					theclosure[z].fatherpoint[theclosure[z].fathercount] = ne;
					//theclosure[now].scount++;
					theclosure[now].next[theclosure[now].scount] = z;//����ǰ��Ŀ����nextָ���ҵ�����Ŀ��
					string strin = xiangmu[theclosure[now].all[theclosure[now].scount]].first.second;
					char cha[100];
					strcpy(cha, strin.c_str());
					string nt;
					nt.push_back(cha[xiangmu[theclosure[now].all[theclosure[now].scount]].second]);
					theclosure[now].nextpoint[theclosure[now].scount] = nt;//�����ɨ���ַ����ĵ�һ���ַ���һ���ַ�������һ����Ŀ��
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
		flag = searchson();//Ѱ�һ�û�ж�Ӧ��ϵ����Ŀ���е���Ŀ
		/*string st = xiangmu[theclosure[now].all[0]].first.second;
		char ch[100];
		strcpy(ch, st.c_str());
		string ne;
		ne.push_back(ch[theclosure[now].spot]);
		if (vn.count(ne) == 1)dfs(now, ne);*/
		//now++;
		for (int m = 0; m <= num_closure; m++)//����ÿ��closure��
		{
			now = m;//��ǰ��Ŀ
			while (theclosure[now].scount != theclosure[now].count)//
			{
				theclosure[now].scount++;//������û�ж�Ӧ�ģ�����Ҫ���ӣ����Բ��õ������ڹ�Լ��Ŀ���µ���ѭ��
				pair<pair<string, string>, int>str1 = xiangmu[theclosure[now].all[theclosure[now].scount]];//û���Ӵ�����Ŀ
				int i = str1.second+1;//�����һλ +1�У���+1���У�����ǹ�Լ��Ŀ������֮��Ѱ�Һ��Ӧ����һ�������ڵļ���
				for (int x = 0; x < num_xiangmu; x++)//������Ŀ��������ͬ����Ŀ��
				{
					if (str1.first == xiangmu[x].first && i == (xiangmu[x].second))//�����ڵĻ���������Ȼû�У������Ӵ�scount�������ӵ�
					{
						int z = search(x);//����Ŀ��
						int exist = searchexist(x);//�ж��Ƿ����һ����Ŀ������Ŀ���ĵ�һ��
						if (exist != -1)z = exist;
						if (z == -1)//�Ҳ���
						{
							int a = searchsameth(x,now);//�ҵ�ǰ׺��ͬ����Ŀ����Ŀ��
							if (a == -1)//�Ҳ���
							{
								num_closure++;//��Ŀ����������
								int n = num_closure;
								theclosure[n].num = n;//��ֵ
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
								if (vn.count(nex) == 1)dfs(n, nex);//���
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
	for (int i = 0; i <=num_closure; i++)//�����Ŀ��
	{
		cout << "I" << i << endl;
		for (int x = 0; x <= theclosure[i].count; x++)
		{
			cout<<xiangmu[theclosure[i].all[x]].first.first << "->" << xiangmu[theclosure[i].all[x]].first.second <<"\t.��"<< xiangmu[theclosure[i].all[x]].second <<"\t"<<theclosure[i].next[x]<<"\t"<< theclosure[i].nextpoint[x] <<"\t"<< endl;
		}
		cout << endl;
	}
}
int GO(int x,string n)//��Ŀ����ţ�����
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
		next.push_back(ch[str.second]);//��ȡ�������ַ�
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
int gogo(int x, string n)//��Ŀ����ţ������ַ�
{//����ֱ��ͨ��nextpoint �Լ�next��ȷ����һ����Ŀ������Ϊ�˰�ȫ���Ƚ�����֤
	string stri = "";
	for (int i = 0; i <= theclosure[x].count; i++)//������Ŀ���е���Ŀ
	{
		int y = theclosure[x].all[i];
		pair < pair<string, string>, int >str = xiangmu[y];
		char ch[100];
		string st = str.first.second;
		strcpy(ch, st.c_str());
		string next;
		next.push_back(ch[str.second]);//��ȡ��ɨ����Ŵ��ĵ�һ������
		if (next == n) {//�ҵ���Ӧ�����룬��Ӧ����Ŀ
			str.second++;//����ƣ���ȡ��Ŀ
			for (int z = 0; z < num_xiangmu; z++)//������Ŀ
			{
				if (str == xiangmu[z])//�ҵ���Ӧ����Ŀ������ǹ�Լ��Ŀ�Ļ�������ƣ��ͻ��Ҳ�����Ŀ��
				{//��z
					if (theclosure[x].next[i] != NULL) {//��Ŀ��ȡһ���ַ�����һ����Ŀ��
						int a = theclosure[x].next[i];
						for (int b = 0; b <= theclosure[a].count; b++)//����next��Ŀ������Ŀ
						{
							if (theclosure[a].all[b] == z)return a;//���ڵ���ƺ����Ŀ��֤������Ŀ��������Ҫ�ļ��ϵı��
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
	for (int z = 0; z <= num_closure; z++)//ÿ�������е�ÿ����Ŀ����һ�ι�����ͬ�ĻḲ��
	{
		for (int f = 0; f <= theclosure[z].count;f++)
		{
			int i = theclosure[z].all[f];
			if (xiangmu[i].first.second.length() == xiangmu[i].second)//��Լ��Ŀ
			{
				//cout << "a" << endl;
				if (i == 1) {//acc��������Ŀһ���ڹ̶�λ��
					int x = search(i);
					Action[x][vt["#"]] = "acc";
				}
				else {//r
					int x = search(i);
					/*cout << x << endl;
					cout << xiangmu[i].first.first << "->" << xiangmu[i].first.second << "����" << xiangmu[i].second << endl;*/
					pair<string, string>str = xiangmu[i].first;
					int n = wherechanshengshi[str];//����ʽλ��
					for (int h = 0; h < num_vt; h++)
					{
						Action[x][h] = "r" + to_string(n);//r+��Ų���ʽλ��
					}
				}
			}
			else {
				//int x = search(i);
				//cout << z << endl;
				//cout << xiangmu[i].first.first << "->" << xiangmu[i].first.second << "����" << xiangmu[i].second << endl;
				char ch[100];
				string str = xiangmu[i].first.second;
				strcpy(ch, str.c_str());
				string next;
				next.push_back(ch[xiangmu[i].second]);//��ȡ�����ַ��������ȡ������
				//cout << "\"" << next << "\"" << endl;
				if (vn.count(next) == 1)//���ս������Լ��Ŀ
				{
					int y = GoGo(z, next);//������Ŀ��
					//cout << "->" << y << "<-" << endl;
					if (y != -1)Goto[z][vn[next]] = to_string(y);
				}
				if (vt.count(next) == 1)//�ս�����ƽ���Ŀ
				{
					int y = GoGo(z, next);//������Ŀ��
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
	cout << "���봮������#" ;
	//cin >> code;
	code = "i+i*i";
	cout << "������Ҫ���������봮���ַ�����(������#)��"<<endl;
	cin >> b;
	b = b + 1;
	string input;
	cout << "������Ҫ���������봮(#Ϊ��β��:";
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
	int n = 0;//���봮ָ��λ��
	cout << endl;
	while (1)
	{
		showstackch();
		showstackstatus();
		int x = status.top();
		string z = Action[x][vt[strcode[n]]];//��action��
		string temp = z.substr(0, 1);//��ȡ�ַ����еĵ�һ���ַ����ж���r��s
		string num;
		for (int j = n; j < b; j++)//������봮
		{
			cout << strcode[j];
		}
		cout << "\t";
		if(z.length()>1)num = z.substr(1);//��ȡ����
		if (temp == "s")//�ƽ�
		{
			cout << num << "��ջ" << endl;
			status.push(atoi(num.c_str()));//״̬��ջ
			ch.push(strcode[n]);//�����ַ���ջ
			n++;//��һ���ַ�
		}
		else if (temp == "r")//��Լ
		{
			int n = atoi(num.c_str());//ת��Ϊ����
			cout << "��" << chanshengshi[n].first << "->" << chanshengshi[n].second << "��Լ"<<endl;
			for (int i = 0; i < chanshengshi[n].second.length(); i++)
			{
				status.pop();//��ջ
				ch.pop();//��ջ
			}
			ch.push(chanshengshi[n].first);//������ջ
			string g = Goto[status.top()][vn[ch.top()]];//��ȡgoto���״̬
			int j = atoi(g.c_str());
			status.push(j);//״̬��ջ
		}
		else if (z == "acc")
		{
			cout << "�����ɹ�" << endl;
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
			cout << "�ɹ�" << endl;
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