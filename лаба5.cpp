#include <stdlib.h>
#include <stdio.h>

char out[200], * pout = out;
char s[80] = "(Ivan, Petr, Fedr =Jil-bil * u samogo (Sinego,Belogo,jeltogo =*)  morya!)";

char* step(char* st)
{
	char* pst = st, * pi;
	while (*pst != '=')
		pst++; // We put it on the equal symbol
	pst++;
	for (pi = st; *(pi - 1) != '='; pi++)
	{
		if (*pst == ')') return pst + 1;
		while (*pst != '*')
			*pout++ = *pst++;
		while (*pi != ',' && *pi != '=')
			*pout++ = *pi++;
		pst++;
		while (*pst != ')')
		{
			if (*pst == '(')
			{
				pst++;
				pst = step(pst);
			}
			*pout++ = *pst++;
		}
	}
}
int main()
{
	char* ps = s;
	for (; *ps != 0; ps++)
		if (*ps != '(')
		{
			*pout++ = *ps;
		}
		else
		{
			ps++;
			ps = step(ps);
		}
	*pout = 0;
	printf("%s ", out);
}
