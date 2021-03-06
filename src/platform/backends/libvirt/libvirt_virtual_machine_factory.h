/*
 * Copyright (C) 2018 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef MULTIPASS_LIBVIRT_VIRTUAL_MACHINE_FACTORY_H
#define MULTIPASS_LIBVIRT_VIRTUAL_MACHINE_FACTORY_H

#include <multipass/virtual_machine_factory.h>

#include <memory>

#include <libvirt/libvirt.h>

namespace multipass
{
class LibVirtVirtualMachineFactory final : public VirtualMachineFactory
{
public:
    using ConnectionUPtr = std::unique_ptr<virConnect, decltype(virConnectClose)*>;

    explicit LibVirtVirtualMachineFactory(const Path& data_dir);
    ~LibVirtVirtualMachineFactory();

    VirtualMachine::UPtr create_virtual_machine(const VirtualMachineDescription& desc,
                                                VMStatusMonitor& monitor) override;
    void remove_resources_for(const std::string& name) override;
    FetchType fetch_type() override;
    VMImage prepare_source_image(const VMImage& source_image) override;
    void prepare_instance_image(const VMImage& instance_image, const VirtualMachineDescription& desc) override;
    void configure(const std::string& name, YAML::Node& meta_config, YAML::Node& user_config) override;
    void check_hypervisor_support() override;

private:
    ConnectionUPtr connection;
    const std::string bridge_name;
};
}

#endif // MULTIPASS_LIBVIRT_VIRTUAL_MACHINE_FACTORY_H
