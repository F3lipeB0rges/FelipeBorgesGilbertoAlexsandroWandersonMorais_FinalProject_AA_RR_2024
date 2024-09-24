import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter, MultipleLocator

# Tamanhos de entrada e tempos correspondentes
entradas = [
    ("tartarugas_ninjas", 0.223),
    ("biblia", 0.446),
    ("historia_humanidade", 1.273),
    ("flamengo_2017", 2.072),
    ("bens_tombados", 2.472)
]

# Extraindo os tempos e nomes para plotar
nomes = [nome for nome, _ in entradas]
tempos = [tempo for _, tempo in entradas]

def format_func(value, tick_number):
    return f"{value:.1f}"  # Formata os tempos para mostrar 1 casa decimal

plt.figure(figsize=(10, 6))
plt.plot(nomes, tempos, color='r')
plt.title('Tempo de Execução do Algoritmo por Entrada')
plt.xlabel('Identificação da Entrada')
plt.ylabel('Tempo de Execução (s)')

# Define a escala do eixo y
plt.ylim(0, max(tempos) + 0.5)  # Ajuste o limite superior conforme necessário
plt.gca().yaxis.set_major_locator(MultipleLocator(0.1))  # Intervalo de 0,1 segundos
plt.gca().yaxis.set_major_formatter(FuncFormatter(format_func))
plt.grid(axis='y', linestyle='--')

plt.show()
