#include "layer.h"

/* The sigmoid function and derivative. */
double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double sigmoidprime(double x) {
    return x * (1 - x);
}

/* Creates a single layer. */
layer_t *layer_create(void) {
    layer_t *layer;
    layer = malloc(sizeof(layer_t));
    if (layer == NULL) {
        perror("Error allocating memory for layer");
        return NULL;
    }
    //same as (*layer).num_inputs = 0;
    layer->num_inputs = 0;
    layer->num_outputs = 0;
    return layer;

}

/* Initialises the given layer. */
bool layer_init(layer_t *layer, int num_outputs, layer_t *prev) {
    layer->num_outputs = num_outputs;
    layer->prev = prev;
    layer->outputs = calloc(num_outputs, sizeof(double));
    if (layer->outputs == NULL) {
        return true;
    }
    //if this is not the initialisation layer
    if (prev != NULL) {
        layer->num_inputs = prev->num_outputs;
        //allocates the weights, biases and deltas arrays.
        layer->biases = calloc(num_outputs, sizeof(double));
        layer->deltas = calloc(num_outputs, sizeof(double));
        layer->weights = malloc(sizeof(double *) * layer->num_inputs);
        //if any assignment fails, return true;
        if (layer->biases == NULL || layer->deltas == NULL || layer->weights == NULL) {
            return true;
        }
        for (int i = 0; i < layer->num_inputs; i++) {
            layer->weights[i] = malloc(sizeof(double) * num_outputs);
            if (layer->weights[i] == NULL) {
                return true;
            }
            for (int j = 0; j < layer->num_outputs; j++) {
                //assign randomly the weights
                layer->weights[i][j] = ANN_RANDOM();
            }
        }
    }
    return false;
}

/* Frees a given layer. */
void layer_free(layer_t *layer) {
    free(layer->outputs);
    //if it is not the initialisation layer, then things have been initialised and need to be freed.
    //if it is the initialisation layer, just free the layer.
    if (layer->prev != NULL) {
        free(layer->biases);
        free(layer->deltas);
        for (int i = 0; i < layer->num_inputs; i++) {
            free(layer->weights[i]);
        }
        free(layer->weights);
    }
    free(layer);
}

/* Computes the outputs of the current layer. */
void layer_compute_outputs(layer_t const *layer) {
    if (layer->prev != NULL) {
        for (int j = 0; j < layer->num_outputs; j++) {
            double sum = 0;
            // Oi is previous layer's output
            // Wij is the weight of the connection
            // Bj is the bias of the neuron
            for (int i = 0; i < layer->prev->num_outputs; i++) {
                sum += layer->weights[i][j] * layer->prev->outputs[i];
            }
            layer->outputs[j] = sigmoid(layer->biases[j] + sum);
        }
    }
}

/* Computes the delta errors for this layer. */
void layer_compute_deltas(layer_t const *layer) {
    if (layer->prev != NULL) {
        for (int i = 0; i < layer->num_outputs; i++) {
            double sum = 0;
            for (int j = 0; j < layer->next->num_outputs; j++) {
                sum += layer->next->weights[i][j] * layer->next->deltas[j];
            }
            layer->deltas[i] = sigmoidprime(layer->outputs[i]) * sum;
        }
    }
}

/* Updates weights and biases according to the delta errors given learning rate. */
void layer_update(layer_t const *layer, double l_rate) {
    if (layer->prev != NULL) {
        //Oi is the previous layer's output
        //Wij is the weight of the connection
        //Bj is the bias of the neuron
        for (int i = 0; i < layer->prev->num_outputs; i++) {
            for (int j = 0; j < layer->next->num_outputs; j++) {
                layer->weights[i][j] += l_rate * layer->prev->outputs[i] * layer->deltas[j];
                layer->biases[j] += l_rate * layer->deltas[j];
            }
        }
    }
}
