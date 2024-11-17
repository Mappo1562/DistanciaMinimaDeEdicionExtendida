import random


def desordenar_y_ajustar_tamano(s):
    # Generar un nuevo tamaño:
    nuevo_tamano = len(s) # random.randint(max(1, len(s) - 2), len(s) + 2)
    caracteres = list(s)
    random.shuffle(caracteres)
    if nuevo_tamano > len(caracteres):
        caracteres += random.choices(caracteres, k=nuevo_tamano - len(caracteres))
    elif nuevo_tamano < len(caracteres):
        caracteres = caracteres[:nuevo_tamano]
    return ''.join(caracteres)

# ingrese el objetivo aqui:
objetivo = "abcabcabcaabc"
palabra = desordenar_y_ajustar_tamano(objetivo)
archivo = open("entrada.txt","w")
archivo.write(palabra+"\n"+objetivo+"\n")
archivo.close()