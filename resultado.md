CPU: AMD Ryzen 5 7600 6 cores 12 threads 3.8Ghz
SSD: Kingston NV2 PCIe 4.0 NVMe M.2 1TB 3500MB/s
GPU: GALAX NVIDIA GeForce RTX 4060


Tabela     CPU (ms)     GPU (ms)     Speedup
128x128        4.30        1.20        3.58x
512x512      142.20        2.10       67.71x
1044x1044   1161.70        6.10      190.44x



A GPU já venceu desde o menor teste (128x128), com speedup de 3,58x, mas ainda sem muita expressividade. E a partir de 512x512 que o paralelismo da placa mãe destaca-se com 67,71x de speedup, chegando a 190x em 1044x1044, enquanto o processador leva mais de 1 segundo para concluir a mesma operação.
Isso acontece porque matrizes pequenas não têm trabalho suficiente para inicializar o pipeline e despachar os workgroups na GPU. Conforme o tamanho cresce, o custo de preparação deixa de fazer diferença e os milhares de núcleos da GPU passam a processar múltiplas linhas e colunas simultaneamente, algo que a CPU, não consegue replicar nesse tipo de carga massivamente paralela.

