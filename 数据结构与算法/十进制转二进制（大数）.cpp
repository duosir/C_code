#include<stdio.h>
#include<string.h> 
int main(){
	char a[205];//��Ϊ�����޿ո��������ַ������������ 
	while(~scanf("%s",a)){
		int len=strlen(a),ten[205],bin[1000],j=0,bj=0;
		for(int i=0;i<len;i++)//����������ten[] 
			ten[i]=a[i]-'0';
		while(j<len){
			for(int i=j;i<len;i++){
				if(i==len-1){//��ǰλ��ĩλ ,!!!ĩλҪ�ȿ��ǣ������� 
					if(ten[i]%2)//ĩλΪ��������1��bin[] 
						bin[bj++]=1;
					else//ĩλΪż������0��bin[] 
						bin[bj++]=0;
					ten[i]/=2;
					if(j==len-1&&ten[i]==0) //����2����ֻʣ���һλ��Ϊ0��j++,ʹ֮�˳�while��for 
						j++;
				}
				else if(ten[i]%2==0&&ten[i])//��ǰλ��ż���ҷ�0 
					ten[i]/=2;
				else if(ten[i]%2&&i<len-1){//��ǰλ�������ҷ�0�ҷ�ĩλ 
					ten[i]/=2;
					if(!ten[i]) //����λ��Ϊ0
						if(i==j)//�ǵ�һλ��j��1 
							j++;
					ten[i+1]+=10;
				}//else if(!ten[i])//����λΪ0��ɶҲ���� 
			}
		} 
		for(int i=bj-1;i>=0;i--)
			printf("%d",bin[i]);
		puts("");
	}
}
