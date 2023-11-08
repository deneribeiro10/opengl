#include "object.h"
#include "loadobject.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
using namespace std;

class Arm : public vector<object*> {
    object *shoulder, *elbow, *hand, *fixed[2], *fingerArticulation[2], *finger[2];
    object *arm, *forearm;

    vector<glm::mat4> defaultModelMatrix;

public:
    Arm() {
        shoulder = read_obj_file("../models/esfera.obj");
        arm = read_obj_file("../models/cubo.obj");
        elbow = read_obj_file("../models/esfera.obj");
        forearm = read_obj_file("../models/cubo.obj");
        hand = read_obj_file("../models/esfera.obj");
        fixed[0] = read_obj_file("../models/cubo.obj");
        fixed[1] = read_obj_file("../models/cubo.obj");
        fingerArticulation[0] = read_obj_file("../models/esfera.obj");
        fingerArticulation[1] = read_obj_file("../models/esfera.obj");
        finger[0] = read_obj_file("../models/cubo.obj");
        finger[1] = read_obj_file("../models/cubo.obj");

        this->push_back(shoulder);
        this->push_back(arm);
        this->push_back(elbow);
        this->push_back(forearm);
        this->push_back(hand);
        this->push_back(fixed[0]);
        this->push_back(fixed[1]);
        this->push_back(fingerArticulation[0]);
        this->push_back(fingerArticulation[1]);
        this->push_back(finger[0]);
        this->push_back(finger[1]);

        shoulder->Model(
            glm::mat4(1.0)
        );
        defaultModelMatrix.push_back(shoulder->get_Model_matrix());

        arm->Model(
            glm::scale(
                glm::translate(
                    glm::mat4(1.0),
                    glm::vec3(2.0, 0.0, 0.0)
                ),
                glm::vec3(2.0, 0.5, 0.5)
            )
        );
        defaultModelMatrix.push_back(arm->get_Model_matrix());

        elbow->Model(
            glm::scale(
                glm::translate(
                    glm::mat4(1.0),
                    glm::vec3(4.0, 0.0, 0.0)
                ),
                glm::vec3(0.75, 0.75, 0.75)
            )
        );
        defaultModelMatrix.push_back(elbow->get_Model_matrix());

        forearm->Model(
            glm::scale(
                glm::translate(
                    glm::mat4(1.0),
                    glm::vec3(6.0, 0.0, 0.0)
                ),
                glm::vec3(2.0, 0.25, 0.25)
            )
        );
        defaultModelMatrix.push_back(forearm->get_Model_matrix());

        hand->Model(
            glm::scale(
                glm::translate(
                    glm::mat4(1.0),
                    glm::vec3(8.0, 0.0, 0.0)
                ),
                glm::vec3(0.5, 0.5, 0.5)
            )
        );
        defaultModelMatrix.push_back(hand->get_Model_matrix());

        fixed[0]->Model(
            glm::scale(
                glm::translate(
                    glm::rotate(
                        glm::translate(
                            glm::mat4(1.0),
                            glm::vec3(8.0, 0.0, 0.0)
                        ),
                        glm::radians(45.0f),
                        glm::vec3(0.0, 0.0, 1.0)
                    ),
                    glm::vec3(1.0, 0.0, 0.0)
                ),
                glm::vec3(1.0, 0.25, 0.25)
            )
        );
        defaultModelMatrix.push_back(fixed[0]->get_Model_matrix());

        fixed[1]->Model(
            glm::scale(
                glm::translate(
                    glm::rotate(
                        glm::translate(
                            glm::mat4(1.0),
                            glm::vec3(8.0, 0.0, 0.0)
                        ),
                        glm::radians(-45.0f),
                        glm::vec3(0.0, 0.0, 1.0)
                    ),
                    glm::vec3(1.0, 0.0, 0.0)
                ),
                glm::vec3(1.0, 0.25, 0.25)
            )
        );
        defaultModelMatrix.push_back(fixed[1]->get_Model_matrix());

        fingerArticulation[0]->Model(
            glm::scale(
                glm::translate(
                    glm::rotate(
                        glm::translate(
                            glm::mat4(1.0),
                            glm::vec3(8.0, 0.0, 0.0)
                        ),
                        glm::radians(45.0f),
                        glm::vec3(0.0, 0.0, 1.0)
                    ),
                    glm::vec3(2.0, 0.0, 0.0)
                ),
                glm::vec3(0.35, 0.35, 0.35)
            )
        );
        defaultModelMatrix.push_back(fingerArticulation[0]->get_Model_matrix());

        fingerArticulation[1]->Model(
            glm::scale(
                glm::translate(
                    glm::rotate(
                        glm::translate(
                            glm::mat4(1.0),
                            glm::vec3(8.0, 0.0, 0.0)
                        ),
                        glm::radians(-45.0f),
                        glm::vec3(0.0, 0.0, 1.0)
                    ),
                    glm::vec3(2.0, 0.0, 0.0)
                ),
                glm::vec3(0.35, 0.35, 0.35)
            )
        );
        defaultModelMatrix.push_back(fingerArticulation[1]->get_Model_matrix());

        finger[0]->Model(
            glm::scale(
                glm::translate(
                    glm::rotate(
                        glm::translate(
                            glm::mat4(1.0),
                            glm::vec3(8.0, 0.0, 0.0)
                        ),
                        glm::radians(45.0f),
                        glm::vec3(0.0, 0.0, 1.0)
                    ),
                    glm::vec3(3.0, 0.0, 0.0)
                ),
                glm::vec3(1.0, 0.25, 0.25)
            )
        );
        defaultModelMatrix.push_back(finger[0]->get_Model_matrix());

        finger[1]->Model(
            glm::scale(
                glm::translate(
                    glm::rotate(
                        glm::translate(
                            glm::mat4(1.0),
                            glm::vec3(8.0, 0.0, 0.0)
                        ),
                        glm::radians(-45.0f),
                        glm::vec3(0.0, 0.0, 1.0)
                    ),
                    glm::vec3(3.0, 0.0, 0.0)
                ),
                glm::vec3(1.0, 0.3, 0.3)
            )
        );
        defaultModelMatrix.push_back(finger[1]->get_Model_matrix());
    }

    void setShoulderAngleDegrees(float x, float y, float z) {
        // dependency of shoulder
        for(int i : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) {
            (*this)[i]->Model(
                glm::rotate(
                    glm::rotate(
                        glm::rotate(
                            glm::mat4(1.0),
                            glm::radians(x),
                            glm::vec3(1.0, 0.0, 0.0)
                        ),
                        glm::radians(y),
                        glm::vec3(0.0, 1.0, 0.0)
                    ),
                    glm::radians(z),
                    glm::vec3(0.0, 0.0, 1.0)
                )
                *
                defaultModelMatrix[i]
            );
        }
    }

    void setElbowAngleDegrees(float z) {
        // dependency is from index 2 forward
        for(int i : {2, 3, 4, 5, 6, 7, 8, 9, 10}) {
            (*this)[i]->Model(
                elbow->get_Model_matrix()
                *
                glm::rotate(
                    glm::mat4(1.0),
                    glm::radians(z),
                    glm::vec3(0.0, 0.0, 1.0)
                )
                *
                glm::inverse(elbow->get_Model_matrix())
                *
                (*this)[i]->get_Model_matrix()
            );
        }
    }

    void setHandAngleDegrees(float x) {
        for(int i : {4, 5, 6, 7, 8, 9, 10}) {
            (*this)[i]->Model(
                hand->get_Model_matrix()
                *
                glm::rotate(
                    glm::mat4(1.0),
                    glm::radians(x),
                    glm::vec3(1.0, 0.0, 0.0)
                )
                *
                glm::inverse(hand->get_Model_matrix())
                *
                (*this)[i]->get_Model_matrix()
            );
        }
    }

    void setFingerAngleDegrees(float z) {
        for(int i : {7, 9}) {
            (*this)[i]->Model(
                fingerArticulation[0]->get_Model_matrix()
                *
                glm::rotate(
                    glm::mat4(1.0),
                    glm::radians(-z),
                    glm::vec3(0.0, 0.0, 1.0)
                )
                *
                glm::inverse(fingerArticulation[0]->get_Model_matrix())
                *
                (*this)[i]->get_Model_matrix()
            );
        }

        for(int i : {8, 10}) {
            (*this)[i]->Model(
                fingerArticulation[1]->get_Model_matrix()
                *
                glm::rotate(
                    glm::mat4(1.0),
                    glm::radians(z),
                    glm::vec3(0.0, 0.0, 1.0)
                )
                *
                glm::inverse(fingerArticulation[1]->get_Model_matrix())
                *
                (*this)[i]->get_Model_matrix()
            );
        }
    }
};