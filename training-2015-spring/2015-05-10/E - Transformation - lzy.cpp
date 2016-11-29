#include <cstdio>
#include <cmath>

#define x1 x[i]
#define x2 x[i+1]
#define y1 y[i]
#define y2 y[i+1]

int T,n;
double xx,yy,x[100009],y[100009];

double sqr(double x)
{
	return x*x;
}
double cub(double x)
{
	return x*x*x;
}
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&n);
		for (int i=0;i<n;++i)
		{
			scanf("%lf%lf",x+i,y+i);
			//x[i]=xx*cos(yy);
			//y[i]=xx*sin(yy);
		}
		x[n]=x[0];
		y[n]=y[0];
		double s=0.0;
		double k,u,v,w;
		for (int i=0;i<n;++i)
		{
			if (y2==y1) continue;
			k=(x2-x1)/(y2-y1);
			u=1.0/3.0*sqr(k)*(cub(y2)-cub(y1));
			v=(k*x1-sqr(k)*y1)*(sqr(y2)-sqr(y1));
			w=(sqr(x1)+sqr(k*y1)-2*k*x1*y1)*(y2-y1);
			s+=u+v+w;
		}
		printf("%.8f\n",fabs(s)/2.0);
	}
	return 0;
}
