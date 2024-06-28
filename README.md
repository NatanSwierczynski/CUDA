# CUDA

Generowanie i wizualizacja zbioru Mandelbrota

Glowne zalozenia projektu:
- Wygenerowanie zbioru Mandelbrota i jego wizualizacja na - CPU
- Zrównoleglenie obliczeń za pomocą CUDA
- Porównanie wyników

Zbiór Mandelbrota (zwany też żukiem Mandelbrota) jest to podzbiór płaszczyzny zespolonej, którego brzeg jest jednym z najbardziej znanych fraktali, „najsłynniejszym obiektem współczesnej matematyki"
![image](https://github.com/NatanSwierczynski/CUDA/assets/106707211/ce155a76-417a-4c78-a70d-ae105615aa30)

Zbiór może zostać opisany tym równaniem rekurencyjnym:

![image](https://github.com/NatanSwierczynski/CUDA/assets/106707211/dbc2d43c-f714-4afa-b321-16f41dfb937c)

    gdzie p oznacza dowolną liczbę zespoloną

Jeśli wynik nie dąży do nieskończoności to dany punkt należy do zbioru
Wszystko co należy do zbioru Mandelbrota musi być w odległości 2 od środka płaszczyzny.

Zrównoleglenie wyliczenia zbioru Manedlbrota.
Wyliczenie zbioru mandelbrota na architekturze CUDA poprzez podzielenie obliczania całej płaszczyzny liczb zespolonych na fragmenty, które będą wyliczane przez poszczególne bloki wątków.
![image](https://github.com/NatanSwierczynski/CUDA/assets/106707211/46848210-b069-47c2-b2a5-816a2b1dd41e)

Sprzęt wykorzystany do obliczeń:
- GPU [GeForce RTX 2060, dedykowana pamięć 6 GB, 1.920 CUDA cores]
- CPU [intel core i5-9600k 3,7GHz, 6 rdzeni]

Dzialanie aplikacji
Prosty UI:
![image](https://github.com/NatanSwierczynski/CUDA/assets/106707211/14318b66-7d80-430d-86ba-c1a6bba16da0)

![image](https://github.com/NatanSwierczynski/CUDA/assets/106707211/27971efc-f43a-4dd5-bb42-ec3b5ff00e76)

![image](https://github.com/NatanSwierczynski/CUDA/assets/106707211/03c106f4-ee36-4a0a-b65a-861a6cb5c5bd)

![image](https://github.com/NatanSwierczynski/CUDA/assets/106707211/d2868d31-697e-4f29-a646-de1bf338afd8)

![image](https://github.com/NatanSwierczynski/CUDA/assets/106707211/465528f8-5bf3-46c9-ad4e-bf2847aa0d0a)

![image](https://github.com/NatanSwierczynski/CUDA/assets/106707211/e1aa8496-9efd-4d58-a6d4-c355e54659bd)


Porównanie otrzymanych wyników
![image](https://github.com/NatanSwierczynski/CUDA/assets/106707211/ce9bc98b-e563-4e8e-a1de-f12b192e5467)

![image](https://github.com/NatanSwierczynski/CUDA/assets/106707211/ed43d7ea-31fd-4f84-b898-1fa67ed2d433)

![image](https://github.com/NatanSwierczynski/CUDA/assets/106707211/d51fca11-4b5a-44ee-9ae3-deb0318a638c)

![image](https://github.com/NatanSwierczynski/CUDA/assets/106707211/fcb69182-bf3b-488a-992f-6e2917efd8f3)

![image](https://github.com/NatanSwierczynski/CUDA/assets/106707211/6c3d27b3-ce44-405b-8227-33968127eab5)

![image](https://github.com/NatanSwierczynski/CUDA/assets/106707211/24df944a-f433-49c6-a7d7-f05418c21360)

![image](https://github.com/NatanSwierczynski/CUDA/assets/106707211/97f15546-41b3-47e1-8091-857e59689e5e)


Podsumowanie i wnioski
- Zrównoleglenie obliczenia koloru poszczególnych pikseli za pomocą GPU spowodowało przyspieszenie obliczeń, ale dla przypadków z dużą liczbą maksymalnej ilości iteracji.
- Dla przypadków z małą ilością iteracji szybsze były obliczenia sekwencyjne na CPU
- Wraz ze wzrostem ilości pikseli oraz maksymalnej liczby iteracji wzrastało przyspieszenie obliczeń przeprowadzanych na GPU w porównaniu z CPU











