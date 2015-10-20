PROJECT='dcagent'
VERSION='0.0.1'
DEBUG = 1
DEFS =['_DCAGENT_DEBUG']
LIBS = [
        {
            'name':'dcbase',
            'subdir':'base',
            'includes':[],
        },
        {
            'name':'dcnode',
            'subdir':'dcnode',
            'includes':[],
        },
        {
            'name':'dagent',
            'subdir':'dagent',
            'includes':[],
        }
]
EXES = [
        {
            'name':'testagent',
            'subdir':'app/test',
            'includes':[],
            'linkpaths':[],
            'linklibs' : [
                'dagent',
                'dcnode',
                'dcbase',
                'python2.7',
                'protobuf',
            ]
        },
        {
            'name':'reporter',
            'subdir':'app/reporter',
            'includes':[],
            'linkpaths':[],
            'linklibs' : [
                'dagent',
                'dcnode',
                'dcbase',
                'python2.7',
                'protobuf',
            ]
        },
        {
            'name':'collector',
            'subdir':'app/collector',
            'includes':[],
            'linkpaths':[],
            'linklibs' : [
                'dagent',
                'dcnode',
                'dcbase',
                'python2.7',
                'protobuf',
            ]
        },

]
