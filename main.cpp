#include "TarjanNode.hpp"

struct Widget;
using TWT = TarjanNode<Widget>;

struct Widget {
    inline static set<TWT> tarjanNodes;
    set<Widget *> allDependencies;
    set<Widget *> dependencies;
    set<Widget *> dependents;
    TWT *tarjanNode = nullptr;

    void addDependency(Widget &dependency) {
        if (dependencies.emplace(&dependency).second) {
            dependency.dependents.emplace(this);
            if (!tarjanNode) {
                tarjanNode = const_cast<TWT *>(tarjanNodes.emplace(this).first.operator->());
            }
            if (!dependency.tarjanNode) {
                dependency.tarjanNode = const_cast<TWT *>(tarjanNodes.emplace(&dependency).first.operator->());
            }
            tarjanNode->deps.emplace(dependency.tarjanNode);
        }
    }

    string getTarjanNodeName() {
        return "";
    }
};


int main() {

    Widget a, b, c, d, e, f, g;

    a.addDependency(b);
    a.addDependency(c);
    c.addDependency(d);
    c.addDependency(e);
    c.addDependency(f);
    f.addDependency(g);

    TWT::tarjanNodes = &Widget::tarjanNodes;
    TWT::findSCCS();
    TWT::checkForCycle();

    vector<Widget *> sorted = std::move(TWT::topologicalSort);

    for (Widget *widget: sorted) {
        for (Widget *dep: widget->dependencies) {
            widget->allDependencies.emplace(dep);
            for(Widget *d : dep->allDependencies)
            {
                widget->allDependencies.emplace(d);
            }
        }
    }
    auto &k = a.allDependencies;
}
