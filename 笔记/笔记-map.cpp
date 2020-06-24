#include<iostream>
#include<map>
#include<string>
 
using namespace std;
/*优点：有序性，这是map结构最大的优点，其元素的有序性在很多应用中都会简化很多的操作红黑树，
内部实现一个红黑书使得map的很多操作在lgn的时间复杂度下就可以实现，因此效率非常的高。
缺点： 空间占用率高，因为map内部实现了红黑树，虽然提高了运行效率，但是因为每一个节点都需要
额外保存父节点、孩子节点和红/黑性质，使得每一个节点都占用大量的空间
适用处：对于那些有顺序要求的问题，用map会更高效一些。*/
// map实际操作
int main()
{
	// 构造函数
	map<string, int> dict;
	
	// 插入数据的三种方式
	dict.insert(pair<string,int>("apple",2));
	dict.insert(map<string, int>::value_type("orange",3));
	dict["banana"] = 6;
 
	// 判断是否有元素
	if(dict.empty())
		cout<<"该字典无元素"<<endl;
	else
		cout<<"该字典共有"<<dict.size()<<"个元素"<<endl;
 
	// 遍历
	map<string, int>::iterator iter;
	for(iter=dict.begin();iter!=dict.end();iter++)
		cout<<iter->first<<ends<<iter->second<<endl;
 
	// 查找
	if((iter=dict.find("banana"))!=dict.end()) //  返回一个迭代器指向键值为key的元素，如果没找到就返回end()
		cout<<"已找到banana,其value为"<<iter->second<<"."<<endl;
	else
		cout<<"未找到banana."<<endl;
 
	if(dict.count("watermelon")==0) // 返回键值等于key的元素的个数
		cout<<"watermelon不存在"<<endl;
	else
		cout<<"watermelon存在"<<endl;
	
	pair<map<string, int>::iterator, map<string, int>::iterator> ret;
	ret = dict.equal_range("banana"); // 查找键值等于 key 的元素区间为[start,end)，指示范围的两个迭代器以 pair 返回
	cout<<ret.first->first<<ends<<ret.first->second<<endl;
	cout<<ret.second->first<<ends<<ret.second->second<<endl;
 
	iter = dict.lower_bound("boluo"); // 返回一个迭代器，指向键值>=key的第一个元素。
	cout<<iter->first<<endl;
	iter = dict.upper_bound("boluo"); // 返回一个迭代器，指向值键值>key的第一个元素。
	cout<<iter->first<<endl;
	return 0;
}


#include<string>  
#include<iostream>  
#include<unordered_map>
using namespace std;  
  
int main()
{
	unordered_map<string, int>  dict; // 声明unordered_map对象
	
	// 插入数据的三种方式
	dict.insert(pair<string,int>("apple",2));
	dict.insert(unordered_map<string, int>::value_type("orange",3));
	dict["banana"] = 6;
	
	// 判断是否有元素
	if(dict.empty())
		cout<<"该字典无元素"<<endl;
	else
		cout<<"该字典共有"<<dict.size()<<"个元素"<<endl;
	
	// 遍历
	unordered_map<string, int>::iterator iter;
	for(iter=dict.begin();iter!=dict.end();iter++)
		cout<<iter->first<<ends<<iter->second<<endl;
	
	// 查找
	if(dict.count("boluo")==0)
		cout<<"can't find boluo!"<<endl;
	else
		cout<<"find boluo!"<<endl;
	
	if((iter=dict.find("banana"))!=dict.end())
		cout<<"banana="<<iter->second<<endl;
	else
		cout<<"can't find boluo!"<<endl;
	
	return 0;
}

