mynode:
	clang++ -I ../v8/ mynode.cc -o mynode -Wl,-L ../v8/out/native/ -l{v8_{base,libbase,snapshot,libplatform},icu{uc,i18n,data}}  -pthread  -stdlib=libstdc++
