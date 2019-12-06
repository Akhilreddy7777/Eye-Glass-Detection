from tensorflow.tools.graph_transforms import TransformGraph
import tensorflow as tf
import os
from tensorflow.python.framework import ops
def get_graph_def_from_file(graph_filepath):
    with ops.Graph().as_default():
        with tf.gfile.GFile(graph_filepath, 'rb') as f:
            graph_def = tf.GraphDef()
            graph_def.ParseFromString(f.read())
            return graph_def

def optimize_graph(model_dir, graph_filename, transforms, output_node):
    input_names = []
    output_names = [output_node]
    if graph_filename is None:
        graph_def = get_graph_def_from_saved_model(model_dir)
    else:
        graph_def = get_graph_def_from_file(os.path.join(model_dir,
                                                         graph_filename))
    optimized_graph_def = TransformGraph(graph_def, input_names,
                                                 output_names, transforms)
    tf.train.write_graph(optimized_graph_def, logdir=model_dir, as_text=False,
                                                                      name='optimized_model.pb')
    print('Graph optimized!')
#transforms = ['remove_nodes(op=Identity)', 'merge_duplicate_nodes',
#              'strip_unused_nodes','fold_constants(ignore_errors=true)',
#              'fold_batch_norms']
#optimize_graph('/Users/akhilsantha/Desktop/', "frozen_model.pb" , transforms, 'cross_')

transforms = [ 'quantize_weights']

##change the path to your optimized model ##########

optimize_graph('/Users/akhilsantha/Desktop/', "ka_mixed.pb", transforms, 'cross_')
