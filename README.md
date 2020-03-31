[![Build Status](https://travis-ci.org/SergeiNA/reality.svg?branch=master)](https://travis-ci.org/SergeiNA/reality)
# reality (OTUSLesson 31)
solution to otus c++ homework 16

## How to use

**rclst** -- принимает на вход командной строки число ксластеров и имя файла для сохраниния результатов кластеризации и обученной модели
Далее из стандартного входа (cin) читает набор данных
```sh
rclst <n> <outfile> 
```
`n` -- число кластеров
`outfile` -- имя выходных файлов

**Example**: 

```sh
./rclst 100 test1
```

**rclss** -- принимает на вход командной строки имя файла длф чтения  модели и выборки данных с кластерами, на стандартный ввод принимает выборку и по ней выводит наиболее релевантные значения, отсортированные по удалению

```sh
rclss <inputfile> 
```
`inputfile` -- имя входных файлов

**Example**: 

```sh
./rclss test1
```
