 {
    'targets': [
      {
        'target_name': 'mynode',
        'type': 'executable',
        'sources': [
         	'../src/mynode.cc',
		'../src/mynode.h',
		'../src/mynode_main.cc'
        ],
		'include_dirs':[
			'/Users/kenvi/code/study/v8'
		],
        'cflags':[
            '-stdlib=libstdc++',
            '-std=c++0x',
        ],
        'ldflags': [
            '-pthread'
        ]
		#'dependencies':[
        #    'v8_base',
        #    'v8_libbase',
        #    'v8_snapshot',
        #    'v8_libplatform',
        #    'icuuc',
        #    'iuci18n',
        #    'icudata'
		#],
      },
    ],
  }
