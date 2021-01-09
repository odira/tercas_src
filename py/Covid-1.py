import numpy as np
import matplotlib.pyplot as plt

COUNTRY = "Italy"
DAYS_OF_SIMULATION = 366
COEF_BASE = 0.35
COEF_QUARANTINE = 0.135
DAY_QUARANTINE = 74
INCUBATION_PERIOD = 15

# Для воспроизводимости результатов
np.random.seed(0)

# Логика вычисления коэффициента распространения в зависимости от до или после введения карантина.
def get_coef(day):
    return COEF_BASE if day < DAY_QUARANTINE else COEF_QUARANTINE

if __name__ == "__main__":
    # Дни симуляции
    days = np.arange(1, DAYS_OF_SIMULATION)

    # Первый инфицированный
    infected = np.random.randint(1, INCUBATION_PERIOD, 1)

    infected_lst = [] # Список хранит дни зараженных, в которые у них проявится болезнь
    new_cases_lst = []
    new_cases_total_lst = []

    # Цикл симуляции по дням
    for day in days:
        # Берем коэффициент распространения
        coef = get_coef(day)

        # Проверяем зараженных на предмет появления симптомов
        new_cases_idx = np.argwhere(infected == day).flatten()

        # Регистрируем зараженных с симптомами как новые случаи заражения
        new_cases_count = new_cases_idx.size

        # Удаляем зараженных с симптомами из списка инфицированных, способных заражать
        infected = np.delete(infected, new_cases_idx)

        # Генерируем новых зараженных в соответствии с распределением Пуассона и добавляем их к имеющимся
        new_infected_count = np.random.poisson(coef, infected.size).sum()
        new_infected = np.random.randint(1, INCUBATION_PERIOD, new_infected_count) + day
        infected = np.concatenate((infected, new_infected))

        # Заполняем статистику
        infected_lst.append(infected.size)
        new_cases_lst.append(new_cases_count)
        new_cases_total_lst.append(sum(new_cases_lst))

        print(day, infected.size)

    plt.figure(figsize=(16, 8))

    # График общего количества заражений
    plt.subplot(311)
    plt.title(f"COVID-19 pandemic in {COUNTRY}")
    plt.plot(days, new_cases_total_lst)
    plt.grid(True)
    plt.legend(["Total cases"], loc='upper left')

    # График новых ежедневных случаев заражения
    plt.subplot(312)
    plt.bar(days, new_cases_lst, alpha=0.7, color='y')
    plt.grid(True)
    plt.legend(["New cases"], loc='upper left')

    # График ежедневного количества инфицированных
    plt.subplot(313)
    plt.plot(days, infected_lst, color='r')
    plt.grid(True)
    plt.legend(["Infected"], loc='upper left')

    plt.show()

