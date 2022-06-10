#include "ann.h"

/* Creates and returns a new ann. */
ann_t *ann_create(int num_layers, int *layer_outputs) {
    //num_layers = number of layers in ann
    //layer_outputs = array of number of neurons in each layer
    //layer_outputs[0] = number of neurons in input layer
    //layer_outputs[num_layers-1] = number of neurons in output layer


    if (num_layers < 2) {
        // must always have an input and output layer
        return NULL;
    }

    //allocate memory for ann
    ann_t *ann = malloc(sizeof(ann_t));
    if (ann == NULL) {
        return NULL;
    }

    //doubly linked list therefore need to set prev and curr pointers
    layer_t *prev, *curr;

    //allocate memory for input layer and initialise it
    ann->input_layer = layer_create();
    layer_init(ann->input_layer, layer_outputs[0], NULL);

    //assign prev to the input layer
    prev = ann->input_layer;

    for (int i = 1; i < num_layers; i++) {
        //create the next layers and check if allocation has failed or not
        curr = layer_create();
        if (curr == NULL) {
            return NULL;
        }
        layer_init(curr, layer_outputs[i], prev);
        prev->next = curr;
        prev = curr;
    }

    // assign the output layer to current layer
    ann->output_layer = curr;
    curr->prev = ann->output_layer->prev;

    ann->output_layer->next = NULL;
    return ann;
}

/* Frees the space allocated to ann. */
void ann_free(ann_t *ann) {
    layer_t *layer = ann->input_layer;
    while (layer != NULL) {
        layer = layer->next;
        layer_free(layer->prev);
    }
    layer_free(ann->output_layer);
    free(ann);
}

/* Forward run of given ann with inputs. */
void ann_predict(ann_t const *ann, double const *inputs) {
    //need for loop as we need to set every element in inputs to every element in input layers outputs
    for (int i = 0; i < ann->input_layer->num_outputs; ++i) {
        ann->input_layer->outputs[i] = inputs[i];
    }

    layer_t *layer = ann->input_layer;
    while (layer != NULL) {
        layer = layer->next;
        layer_compute_outputs(layer->prev);
    }
    layer_compute_outputs(ann->output_layer);
}

/* Trains the ann with single backprop update. */
void ann_train(ann_t const *ann, double const *inputs, double const *targets, double l_rate) {
    /* Sanity checks. */
    assert(ann != NULL);
    assert(inputs != NULL);
    assert(targets != NULL);
    assert(l_rate > 0);

    /* Run forward pass. */
    ann_predict(ann, inputs);

    /**** PART 2 - QUESTION 4 ****/

    /* 3 MARKS */
}
