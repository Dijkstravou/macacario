import sympy

def generate_prime_lists_tex(file_name='primes_list.tex'):
    # Definir o limite e encontrar todos os números primos até 10.000
    max_prime = 10000
    primes = list(sympy.primerange(1, max_prime + 1))

    # Configuração do documento LaTeX
    tex_content = r"""\documentclass{article}
\usepackage{geometry}
\geometry{a4paper, margin=1in}
\usepackage{multicol}

\begin{document}

\noindent
\textbf{Primos até 10.000} \\
\textit{Existem """ + str(len(primes)) + r""" números primos até 10.000.}

\begin{multicols}{2}
"""

    # Configurar o número de colunas para as listas
    primes_per_list = 150  # Ajuste o número de primos por lista

    # Dividir os números primos em partes menores para múltiplas listas
    for start in range(0, len(primes), primes_per_list):
        list_primes = primes[start:start + primes_per_list]
        tex_content += "\n".join(f"{p}" for p in list_primes)
        tex_content += "\n\n\\vfill\n\n"  # Adiciona espaço vertical para separar listas

    tex_content += r"""
\end{multicols}

\end{document}
"""

    # Escrever o conteúdo LaTeX em um arquivo
    with open(file_name, 'w') as f:
        f.write(tex_content)

    print(f"Arquivo LaTeX '{file_name}' gerado com sucesso.")

# Executa a função para gerar o arquivo LaTeX
generate_prime_lists_tex()
