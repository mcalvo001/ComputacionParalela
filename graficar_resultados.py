import matplotlib.pyplot as plt
import numpy as np

# Datos de ejemplo (reemplaza estos con tus resultados reales)
threads = [1, 2, 4, 8, 16]
tiempo_fuerte = [10, 5.2, 2.8, 1.5, 0.9]  # Ejemplo de tiempos para escalamiento fuerte
tiempo_debil = [10, 10.5, 11, 11.8, 12.5]  # Ejemplo de tiempos para escalamiento débil

# Gráfico de Escalamiento Fuerte
plt.figure(figsize=(10, 5))
plt.subplot(1, 2, 1)
plt.plot(threads, tiempo_fuerte, 'bo-')
plt.title('Escalamiento Fuerte')
plt.xlabel('Número de Hilos')
plt.ylabel('Tiempo de Ejecución (s)')
plt.xscale('log', base=2)
plt.yscale('log', base=2)
plt.grid(True)

# Gráfico de Escalamiento Débil
plt.subplot(1, 2, 2)
plt.plot(threads, tiempo_debil, 'ro-')
plt.title('Escalamiento Débil')
plt.xlabel('Número de Hilos')
plt.ylabel('Tiempo de Ejecución (s)')
plt.xscale('log', base=2)
plt.grid(True)

plt.tight_layout()
plt.show()