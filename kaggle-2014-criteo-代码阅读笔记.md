
# kaggle-2014-criteo-代码阅读笔记

## 主流程解析

主流程采用python脚本。

string.format语法。The str.format() method and the Formatter class share the same syntax.
请参考[Python Format String Syntax 7.1.3](https://docs.python.org/2/library/string.html)

subprocess。请参考[python 子进程](http://www.cnblogs.com/vamei/archive/2012/09/23/2698014.html)，[subprocess docs](https://docs.python.org/2/library/subprocess.html)。

	subprocess.call()：父进程等待子进程完成
	Popen对象创建后，主程序不会自动等待子进程完成。我们必须调用对象的wait()方法，父进程才会等待
	communicate()是Popen对象的一个方法，该方法会阻塞父进程，直到子进程完成。

argparse:用于解析argv参数。参考示例：

	parser = argparse.ArgumentParser()
	parser.add_argument('-s', dest='nr_thread', default=12, type=int)
	parser.add_argument('cvt_path')
	parser.add_argument('src_path')
	parser.add_argument('dst1_path')
	parser.add_argument('dst2_path')
	args = vars(parser.parse_args())

"converters/parallelizer-a.py -s 2 converters/pre-a.py tr.csv tr.gbdt.dense tr.gbdt.sparse"
parallelizer-a.py脚本只是用来做并行化的处理，真正的处理单元是：pre-a.py。

"converters/pre-a.py tr.csv tr.gbdt.dense tr.gbdt.sparse"，该命令主要用于生成标准格式的训练与测试数据。tr.gbdt.dense是处理完后的numerical feature，tr.gbdt.sparse是处理完后的categorial feature。测试数据的label默认都为0。

做完数据预处理A后，接下来就要开始训练GBDT模型了。
其命令行参数为："./gbdt -t 30 -s thread te.gbdt.dense te.gbdt.sparse tr.gbdt.dense tr.gbdt.sparse te.gbdt.out tr.gbdt.out"。

## CART

## GBDT

代码使用了OpenMP。OpenMP是一种面向共享内存以及分布式共享内存的多处理器多线程并行编程语言。
omp_set_num_threads：设置进入并行区域时，将要创建的线程个数。更多请参考[OpenMP常用的库函数](http://blog.csdn.net/donhao/article/details/5651782)

read_dense函数和read_sparse函数的具体解释请参考gbdt的README doc。

GBDT首先需要指定树的个数: "GBDT gbdt(opt.nr_tree)"，然后调用"GBDT::fit(Problem const &Tr, Problem const &Va)"开始训练。


## 编程技巧

[std::vector::shrink_to_fit](http://en.cppreference.com/w/cpp/container/vector/shrink_to_fit)：to reduce capacity() to size()。

[Function template](http://en.cppreference.com/w/cpp/language/function_template) 函数模板。




