#include <math.h>
#include <stdio.h>
#include <stdbool.h>

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

float	decimals(char *str)
{
	int		i;
	float	nbr;
	int		divide;

	i = 0;
	nbr = 0;
	divide = 10;
	while (str[i] != '.' && str[i])
		i++;
	if (str[i] == '.')
		i++;
	while (str[i])
	{
		nbr += str[i] - '0';
		if (str[i + 1] != '\0')
		{
			nbr *= 10;
			divide *= 10;
		}
		i++;
	}
	nbr /= divide;
	return (nbr);
}

float	to_float(char *str)
{
	int		i;
	int		sign;
	float	nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] != '.')
	{
		nbr += (str[i] - '0');
		if (str[i + 1] != '\0' && str[i + 1] != '.')
			nbr *= 10;
		i++;
		printf("nbr: %f\n", nbr);
	}
	printf("nbr: %f\n", nbr);
	return ((nbr + decimals(str)) * sign);
}

int	main(void)
{
	char *str = "-0.75167";
	if (ft_strlen(str) > 8)
		return (0);
	
	printf("hey?\n");
	printf("%f\n", to_float(str));
	return (0);
}