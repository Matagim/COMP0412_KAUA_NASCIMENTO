import subprocess
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sea


subprocess.run(["./quicksort"])
subprocess.run(["./insercao"])
subprocess.run(["./mergesort"])
subprocess.run(["./heapsort2"])

dq = pd.read_csv("tempos_quicksort.csv")
dm = pd.read_csv("tempos_mergesort.csv")
di = pd.read_csv("tempos_insercao.csv")
dh = pd.read_csv("tempos_heapsort.csv")


dados = pd.concat([dq, dm, di, dh])


sea.set(style="whitegrid", font_scale=1.2)

plt.figure(figsize=(10,6))


cores = {
    "Quicksort": "red",
    "Mergesort": "blue",
    "insercao": "green",
    "Heapsort": "yellow"
}


sea.lineplot(
    data=dados,
    x="tamanho",
    y="tempo_medio_s",
    hue="algoritmo",
    style="tipo",
    markers=True,
    dashes=False,
    palette=cores
)

plt.title("Comparação de desempenho entre algoritmos de ordenação")
plt.xlabel("Tamanho do vetor (n)")
plt.ylabel("Tempo médio (segundos)")
plt.legend(title="Algoritmo / Tipo de vetor", loc="best")
plt.tight_layout()
plt.show()