#include<stdio.h>
#include<string.h> 
int main(){
	char a[205];//因为输入无空格，所以用字符数组接受输入 
	while(~scanf("%s",a)){
		int len=strlen(a),ten[205],bin[1000],j=0,bj=0;
		for(int i=0;i<len;i++)//将大数存入ten[] 
			ten[i]=a[i]-'0';
		while(j<len){
			for(int i=j;i<len;i++){
				if(i==len-1){//当前位是末位 ,!!!末位要先考虑！！！！ 
					if(ten[i]%2)//末位为奇数，存1进bin[] 
						bin[bj++]=1;
					else//末位为偶数，存0进bin[] 
						bin[bj++]=0;
					ten[i]/=2;
					if(j==len-1&&ten[i]==0) //除以2除到只剩最后一位且为0，j++,使之退出while和for 
						j++;
				}
				else if(ten[i]%2==0&&ten[i])//当前位是偶数且非0 
					ten[i]/=2;
				else if(ten[i]%2&&i<len-1){//当前位是奇数且非0且非末位 
					ten[i]/=2;
					if(!ten[i]) //若该位变为0
						if(i==j)//是第一位，j加1 
							j++;
					ten[i+1]+=10;
				}//else if(!ten[i])//若该位为0，啥也不干 
			}
		} 
		for(int i=bj-1;i>=0;i--)
			printf("%d",bin[i]);
		puts("");
	}
}
